#pragma once

#include "GreenhouseTypes.h"

namespace greenhouse {

constexpr char kDeviceId[] = "small-greenhouse-01";
constexpr char kFirmwareVersion[] = "0.1.0";

constexpr char kWifiSsid[] = "";
constexpr char kWifiPassword[] = "";

constexpr char kSoracomHost[] = "uni.soracom.io";
constexpr uint16_t kSoracomPort = 80;
constexpr char kSoracomPath[] = "/";

constexpr uint32_t kSerialBaudRate = 115200;
constexpr uint32_t kSerialStartupDelayMs = 1500;
constexpr uint32_t kRuntimeLogIntervalMs = 30000;

// RP2350 / Pico default-capable pin groups.
// Adjust these if your Robo Pico wiring uses a different breakout pair.
constexpr uint8_t kI2cSdaPin = 8;
constexpr uint8_t kI2cSclPin = 9;
constexpr uint8_t kSpiRxPin = 16;
constexpr uint8_t kSpiCsPin = 17;
constexpr uint8_t kSpiSckPin = 18;
constexpr uint8_t kSpiTxPin = 19;

constexpr uint32_t kEnvironmentIntervalMs = 5000;
constexpr uint32_t kMoistureIntervalMs = 10000;
constexpr uint32_t kControlIntervalMs = 1000;
constexpr uint32_t kPublishIntervalMs = 60000;
constexpr uint32_t kPublishRetryIntervalMs = 5000;
constexpr uint32_t kWifiRetryIntervalMs = 15000;
constexpr uint32_t kStartupPumpLockoutMs = 15000;
constexpr uint8_t kPublishQueueDepth = 4;

constexpr float kFanHighTempC = 28.0f;
constexpr float kFanLowTempC = 26.0f;
constexpr uint16_t kCo2LowPpm = 500;
constexpr uint16_t kCo2RecoverPpm = 650;

constexpr uint8_t kUpperFanChannel = 6;
constexpr uint8_t kLowerFanChannel = 7;

constexpr uint8_t kMcp3008CsPin = kSpiCsPin;
constexpr uint32_t kMcp3008SpiClockHz = 1000000;

constexpr uint8_t kOutputHubI2cAddress = 0x20;
constexpr bool kOutputActiveHigh = true;

constexpr const char* kOutputChannelLabels[kOutputChannelCount] = {
    "pump_u1",
    "pump_u2",
    "pump_u3",
    "pump_l1",
    "pump_l2",
    "pump_l3",
    "fan_upper",
    "fan_lower",
};

constexpr uint8_t kStatusLedPin = LED_BUILTIN;
constexpr bool kStatusLedActiveLow = false;

constexpr PotConfig kPots[kPotCount] = {
    {"U1", 0, 0, 780, 430, 35.0f, 48.0f, 4000, 12000, 30UL * 60UL * 1000UL},
    {"U2", 1, 1, 780, 430, 35.0f, 48.0f, 4000, 12000, 30UL * 60UL * 1000UL},
    {"U3", 2, 2, 780, 430, 35.0f, 48.0f, 4000, 12000, 30UL * 60UL * 1000UL},
    {"L1", 3, 3, 780, 430, 35.0f, 48.0f, 4000, 12000, 30UL * 60UL * 1000UL},
    {"L2", 4, 4, 780, 430, 35.0f, 48.0f, 4000, 12000, 30UL * 60UL * 1000UL},
    {"L3", 5, 5, 780, 430, 35.0f, 48.0f, 4000, 12000, 30UL * 60UL * 1000UL},
};

static_assert(kUpperFanChannel < kOutputChannelCount, "Upper fan channel is out of range");
static_assert(kLowerFanChannel < kOutputChannelCount, "Lower fan channel is out of range");

}  // namespace greenhouse
