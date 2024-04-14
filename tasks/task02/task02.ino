#include <TaskManagerIO.h>

struct LED {
  int pin;
  long lastToggle;
  long interval;
  int state;
};

const int LED_COUNT = 5;
LED leds[LED_COUNT] = {
  {3, 0, 50, LOW},
  {5, 0, 100, LOW},
  {6, 0, 500, LOW},
  {9, 0, 1000, LOW},
  {10, 0, 1000, LOW}
};

taskid_t tasks[LED_COUNT];

class Exec : public Executable {
public:
  LED *led;
  void exec() override {
    digitalWrite(led->pin, led->state);
    led->state = (led->state == LOW) ? HIGH : LOW;
  }
} execs[LED_COUNT];

void setup() {
  for (int i = 0; i < LED_COUNT; ++i) {
    execs[i].led = &leds[i];
    pinMode(leds[i].pin, OUTPUT);
    tasks[i] = taskManager.schedule(repeatMicros(leds[i].interval), &execs[i]);
  }
}

void loop() {
  taskManager.runLoop();
}
