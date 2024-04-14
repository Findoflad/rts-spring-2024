struct LED {
  int pin;
  long lastToggle;
  long interval;
  int state;
};

LED leds[] = {
  {3, 0, 50, LOW},
  {5, 0, 100, LOW},
  {6, 0, 500, LOW},
  {9, 0, 1000, LOW},
  {10, 0, 1000, LOW}
};

void setup() {
  for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    pinMode(leds[i].pin, OUTPUT);
  }
}

void loop() {
  unsigned long currentMicros = micros();

  for (int i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
    if (currentMicros - leds[i].lastToggle >= leds[i].interval) {
      leds[i].lastToggle = currentMicros;
      leds[i].state = (leds[i].state == LOW) ? HIGH : LOW;
      digitalWrite(leds[i].pin, leds[i].state);
    }
  }
}
