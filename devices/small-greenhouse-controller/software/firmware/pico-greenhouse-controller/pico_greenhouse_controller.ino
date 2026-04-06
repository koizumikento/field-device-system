#include "GreenhouseController.h"

greenhouse::GreenhouseController controller;

void setup() {
    Serial.begin(greenhouse::kSerialBaudRate);
    delay(greenhouse::kSerialStartupDelayMs);

    const bool ok = controller.begin();
    Serial.println(ok ? F("[gh] controller ready") : F("[gh] controller started with degraded subsystems"));
}

void loop() {
    controller.tick();
    delay(25);
}
