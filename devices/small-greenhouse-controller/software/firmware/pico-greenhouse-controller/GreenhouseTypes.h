#pragma once

#include <Arduino.h>

namespace greenhouse {

constexpr uint8_t kPotCount = 6;
constexpr uint8_t kOutputChannelCount = 8;

struct PotConfig {
    const char* id;
    uint8_t adcChannel;
    uint8_t outputChannel;
    uint16_t adcDry;
    uint16_t adcWet;
    float triggerPercent;
    float recoverPercent;
    uint32_t basePumpMs;
    uint32_t maxPumpMs;
    uint32_t cooldownMs;
};

struct PotState {
    uint16_t rawAdc = 0;
    float moisturePercent = 0.0f;
    bool sensorFault = true;
    bool pumpActive = false;
    uint32_t pumpStartedMs = 0;
    uint32_t pumpDurationMs = 0;
    uint32_t lastWateredMs = 0;
    uint32_t totalWaterings = 0;
};

struct EnvironmentReadings {
    float airTempC = NAN;
    float airHumidityPct = NAN;
    float scdTempC = NAN;
    float scdHumidityPct = NAN;
    uint16_t co2Ppm = 0;
    bool shtOk = false;
    bool scdOk = false;
    bool scdFresh = false;
    uint32_t measuredAtMs = 0;
};

struct AlarmState {
    bool wifiDisconnected = false;
    bool environmentSensorFault = false;
    bool anyMoistureFault = false;
};

struct PublishState {
    bool enabled = false;
    bool lastAttemptOk = false;
    uint16_t lastStatusCode = 0;
    uint32_t lastAttemptMs = 0;
    uint32_t lastSuccessMs = 0;
    uint32_t successCount = 0;
    uint32_t failureCount = 0;
    uint32_t droppedCount = 0;
};

}  // namespace greenhouse
