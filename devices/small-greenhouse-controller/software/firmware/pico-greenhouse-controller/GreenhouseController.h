#pragma once

#include "ActuatorHub.h"
#include "EnvironmentSensors.h"
#include "MoistureHub.h"
#include "SoracomPublisher.h"

namespace greenhouse {

class GreenhouseController {
  public:
    bool begin();
    void tick();

  private:
    void sampleEnvironment();
    void sampleMoisture();
    void updateClimateControl();
    void updateWateringControl();
    void updateActivePump();
    void updatePublisher();
    void updateStatusLed() const;
    void logStartup(bool envOk, bool actuatorOk) const;
    void logPumpStart(uint8_t index) const;
    void logPumpStop(uint8_t index) const;
    void logPublishAttempt(bool ok, uint16_t statusCode) const;
    void logRuntimeSummary() const;
    const char* activePotId() const;
    uint8_t selectNextPotToWater() const;
    uint32_t computePumpDurationMs(uint8_t index) const;
    String buildSnapshotJson() const;
    void enqueuePayload(const String& payload);
    void flushPublishQueue();

    EnvironmentSensors environmentSensors_;
    MoistureHub moistureHub_{kMcp3008CsPin};
    ActuatorHub actuatorHub_;
    SoracomPublisher publisher_;

    EnvironmentReadings environment_;
    PotState pots_[kPotCount];
    AlarmState alarms_;

    bool upperFanEnabled_ = false;
    bool lowerFanEnabled_ = false;
    int8_t activePumpIndex_ = -1;
    uint32_t lastEnvironmentAtMs_ = 0;
    uint32_t lastMoistureAtMs_ = 0;
    uint32_t lastControlAtMs_ = 0;
    uint32_t lastPublishAtMs_ = 0;
    uint32_t lastPublishAttemptAtMs_ = 0;
    uint32_t lastRuntimeLogAtMs_ = 0;

    String queue_[kPublishQueueDepth];
    uint8_t queueHead_ = 0;
    uint8_t queueCount_ = 0;
    PublishState publishState_;
};

}  // namespace greenhouse
