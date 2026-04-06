#include "GreenhouseController.h"

namespace greenhouse {

namespace {

bool elapsed(uint32_t now, uint32_t lastAt, uint32_t intervalMs) {
    return now - lastAt >= intervalMs;
}

const char* boolString(bool value) {
    return value ? "true" : "false";
}

void appendJsonString(String& out, const char* value) {
    out += '"';
    while (*value != '\0') {
        const char c = *value++;
        if (c == '"' || c == '\\') {
            out += '\\';
        }
        out += c;
    }
    out += '"';
}

}  // namespace

bool GreenhouseController::begin() {
    pinMode(kStatusLedPin, OUTPUT);
    updateStatusLed();

    Wire.setSDA(kI2cSdaPin);
    Wire.setSCL(kI2cSclPin);
    Wire.begin();

    SPI.setRX(kSpiRxPin);
    SPI.setSCK(kSpiSckPin);
    SPI.setTX(kSpiTxPin);
    SPI.begin();

    const bool envOk = environmentSensors_.begin(Wire);
    moistureHub_.begin(SPI);
    const bool actuatorOk = actuatorHub_.begin(Wire);
    publisher_.begin();
    publishState_.enabled = publisher_.isEnabled();

    alarms_.environmentSensorFault = !envOk;
    alarms_.wifiDisconnected = publisher_.isEnabled() && !publisher_.isConnected();

    actuatorHub_.allOff();
    sampleEnvironment();
    sampleMoisture();
    logStartup(envOk, actuatorOk);

    return envOk && actuatorOk;
}

void GreenhouseController::tick() {
    const uint32_t now = millis();

    if (elapsed(now, lastEnvironmentAtMs_, kEnvironmentIntervalMs)) {
        sampleEnvironment();
    }
    if (elapsed(now, lastMoistureAtMs_, kMoistureIntervalMs)) {
        sampleMoisture();
    }
    if (elapsed(now, lastControlAtMs_, kControlIntervalMs)) {
        updateClimateControl();
        updateWateringControl();
        lastControlAtMs_ = now;
    }

    updateActivePump();
    updatePublisher();
    updateStatusLed();

    if (elapsed(now, lastRuntimeLogAtMs_, kRuntimeLogIntervalMs)) {
        logRuntimeSummary();
        lastRuntimeLogAtMs_ = now;
    }
}

void GreenhouseController::sampleEnvironment() {
    EnvironmentReadings latest;
    if (!environmentSensors_.read(latest)) {
        alarms_.environmentSensorFault = true;
    } else {
        alarms_.environmentSensorFault = !(latest.shtOk || latest.scdOk);
        environment_ = latest;
    }
    lastEnvironmentAtMs_ = millis();
}

void GreenhouseController::sampleMoisture() {
    moistureHub_.readAll(pots_);

    bool anyFault = false;
    for (uint8_t i = 0; i < kPotCount; ++i) {
        anyFault = anyFault || pots_[i].sensorFault;
    }
    alarms_.anyMoistureFault = anyFault;
    lastMoistureAtMs_ = millis();
}

void GreenhouseController::updateClimateControl() {
    const bool tempDemand = isfinite(environment_.airTempC) && environment_.airTempC >= kFanHighTempC;
    const bool tempRecover = isfinite(environment_.airTempC) && environment_.airTempC <= kFanLowTempC;
    const bool co2Demand = environment_.co2Ppm > 0 && environment_.co2Ppm <= kCo2LowPpm;
    const bool co2Recover = environment_.co2Ppm >= kCo2RecoverPpm;

    if (tempDemand || co2Demand) {
        upperFanEnabled_ = true;
        lowerFanEnabled_ = true;
    } else if (tempRecover && co2Recover) {
        upperFanEnabled_ = false;
        lowerFanEnabled_ = false;
    }

    actuatorHub_.setChannel(kUpperFanChannel, upperFanEnabled_);
    actuatorHub_.setChannel(kLowerFanChannel, lowerFanEnabled_);
}

void GreenhouseController::updateWateringControl() {
    if (activePumpIndex_ >= 0) {
        return;
    }

    const uint32_t now = millis();
    if (now < kStartupPumpLockoutMs) {
        return;
    }

    const uint8_t candidate = selectNextPotToWater();
    if (candidate >= kPotCount) {
        return;
    }

    PotState& pot = pots_[candidate];
    pot.pumpDurationMs = computePumpDurationMs(candidate);
    pot.pumpStartedMs = now;
    pot.pumpActive = true;
    activePumpIndex_ = static_cast<int8_t>(candidate);

    actuatorHub_.setChannel(kPots[candidate].outputChannel, true);
    logPumpStart(candidate);
}

void GreenhouseController::updateActivePump() {
    if (activePumpIndex_ < 0) {
        return;
    }

    PotState& pot = pots_[activePumpIndex_];
    if (millis() - pot.pumpStartedMs < pot.pumpDurationMs) {
        return;
    }

    actuatorHub_.setChannel(kPots[activePumpIndex_].outputChannel, false);
    pot.pumpActive = false;
    pot.lastWateredMs = millis();
    pot.totalWaterings += 1;
    logPumpStop(static_cast<uint8_t>(activePumpIndex_));
    activePumpIndex_ = -1;
}

void GreenhouseController::updatePublisher() {
    publisher_.tick();
    publishState_.enabled = publisher_.isEnabled();
    alarms_.wifiDisconnected = publishState_.enabled && !publisher_.isConnected();
    if (!publishState_.enabled) {
        return;
    }

    if (elapsed(millis(), lastPublishAtMs_, kPublishIntervalMs)) {
        enqueuePayload(buildSnapshotJson());
        lastPublishAtMs_ = millis();
    }

    flushPublishQueue();
}

void GreenhouseController::updateStatusLed() const {
    const bool healthy = !alarms_.environmentSensorFault && !alarms_.wifiDisconnected && !alarms_.anyMoistureFault;
    const bool ledOn = kStatusLedActiveLow ? !healthy : healthy;
    digitalWrite(kStatusLedPin, ledOn ? HIGH : LOW);
}

uint8_t GreenhouseController::selectNextPotToWater() const {
    const uint32_t now = millis();
    float driestPercent = 101.0f;
    uint8_t best = kPotCount;

    for (uint8_t i = 0; i < kPotCount; ++i) {
        const PotConfig& config = kPots[i];
        const PotState& state = pots_[i];

        if (state.sensorFault || state.pumpActive) {
            continue;
        }
        if (state.lastWateredMs != 0 && now - state.lastWateredMs < config.cooldownMs) {
            continue;
        }
        if (state.moisturePercent > config.triggerPercent) {
            continue;
        }
        if (state.moisturePercent < driestPercent) {
            driestPercent = state.moisturePercent;
            best = i;
        }
    }

    return best;
}

uint32_t GreenhouseController::computePumpDurationMs(uint8_t index) const {
    const PotConfig& config = kPots[index];
    const PotState& state = pots_[index];

    const float deficit = max(0.0f, config.triggerPercent - state.moisturePercent);
    const float span = max(1.0f, config.recoverPercent - config.triggerPercent);
    const float ratio = min(1.0f, deficit / span);

    const uint32_t extraMs = static_cast<uint32_t>((config.maxPumpMs - config.basePumpMs) * ratio);
    return config.basePumpMs + extraMs;
}

String GreenhouseController::buildSnapshotJson() const {
    String json;
    json.reserve(1400);

    json += '{';
    json += F("\"device_id\":");
    appendJsonString(json, kDeviceId);
    json += F(",\"firmware\":");
    appendJsonString(json, kFirmwareVersion);
    json += F(",\"uptime_ms\":");
    json += String(millis());
    json += F(",\"wifi\":{\"connected\":");
    json += publisher_.isConnected() ? F("true") : F("false");
    json += F(",\"rssi\":");
    json += String(publisher_.rssi());
    json += '}';

    json += F(",\"environment\":{\"temp_c\":");
    json += String(environment_.airTempC, 2);
    json += F(",\"humidity_pct\":");
    json += String(environment_.airHumidityPct, 2);
    json += F(",\"co2_ppm\":");
    json += String(environment_.co2Ppm);
    json += F(",\"sht_ok\":");
    json += environment_.shtOk ? F("true") : F("false");
    json += F(",\"scd_ok\":");
    json += environment_.scdOk ? F("true") : F("false");
    json += '}';

    json += F(",\"outputs\":{\"upper_fan\":");
    json += upperFanEnabled_ ? F("true") : F("false");
    json += F(",\"lower_fan\":");
    json += lowerFanEnabled_ ? F("true") : F("false");
    json += F(",\"active_pot\":");
    if (activePumpIndex_ >= 0) {
        appendJsonString(json, kPots[activePumpIndex_].id);
    } else {
        json += F("null");
    }
    json += '}';

    json += F(",\"publish\":{\"enabled\":");
    json += publishState_.enabled ? F("true") : F("false");
    json += F(",\"queue_depth\":");
    json += String(queueCount_);
    json += F(",\"last_attempt_ok\":");
    json += publishState_.lastAttemptOk ? F("true") : F("false");
    json += F(",\"last_status_code\":");
    json += String(publishState_.lastStatusCode);
    json += F(",\"success_count\":");
    json += String(publishState_.successCount);
    json += F(",\"failure_count\":");
    json += String(publishState_.failureCount);
    json += F(",\"dropped_count\":");
    json += String(publishState_.droppedCount);
    json += F(",\"last_success_ms\":");
    json += String(publishState_.lastSuccessMs);
    json += '}';

    json += F(",\"pots\":[");
    for (uint8_t i = 0; i < kPotCount; ++i) {
        if (i > 0) {
            json += ',';
        }
        json += '{';
        json += F("\"id\":");
        appendJsonString(json, kPots[i].id);
        json += F(",\"raw_adc\":");
        json += String(pots_[i].rawAdc);
        json += F(",\"moisture_pct\":");
        json += String(pots_[i].moisturePercent, 1);
        json += F(",\"sensor_fault\":");
        json += pots_[i].sensorFault ? F("true") : F("false");
        json += F(",\"pump_active\":");
        json += pots_[i].pumpActive ? F("true") : F("false");
        json += F(",\"pump_channel\":");
        json += String(kPots[i].outputChannel);
        json += F(",\"pump_duration_ms\":");
        json += String(pots_[i].pumpDurationMs);
        json += F(",\"last_watered_ms\":");
        json += String(pots_[i].lastWateredMs);
        json += F(",\"total_waterings\":");
        json += String(pots_[i].totalWaterings);
        json += '}';
    }
    json += ']';

    json += F(",\"alarms\":{\"wifi_disconnected\":");
    json += alarms_.wifiDisconnected ? F("true") : F("false");
    json += F(",\"environment_sensor_fault\":");
    json += alarms_.environmentSensorFault ? F("true") : F("false");
    json += F(",\"any_moisture_fault\":");
    json += alarms_.anyMoistureFault ? F("true") : F("false");
    json += F("}}");

    return json;
}

void GreenhouseController::enqueuePayload(const String& payload) {
    if (queueCount_ == kPublishQueueDepth) {
        queueHead_ = static_cast<uint8_t>((queueHead_ + 1) % kPublishQueueDepth);
        queueCount_ -= 1;
        publishState_.droppedCount += 1;
    }

    const uint8_t tail = static_cast<uint8_t>((queueHead_ + queueCount_) % kPublishQueueDepth);
    queue_[tail] = payload;
    queueCount_ += 1;
}

void GreenhouseController::flushPublishQueue() {
    if (queueCount_ == 0) {
        return;
    }

    const uint32_t now = millis();
    if (!elapsed(now, lastPublishAttemptAtMs_, kPublishRetryIntervalMs)) {
        return;
    }

    lastPublishAttemptAtMs_ = now;
    uint16_t statusCode = 0;
    const bool published = publisher_.publishJson(queue_[queueHead_], statusCode);
    publishState_.lastAttemptMs = now;
    publishState_.lastStatusCode = statusCode;
    publishState_.lastAttemptOk = published;
    if (!published) {
        publishState_.failureCount += 1;
        logPublishAttempt(false, statusCode);
        return;
    }

    publishState_.successCount += 1;
    publishState_.lastSuccessMs = millis();
    queue_[queueHead_].remove(0);
    queueHead_ = static_cast<uint8_t>((queueHead_ + 1) % kPublishQueueDepth);
    queueCount_ -= 1;
    logPublishAttempt(true, statusCode);
}

void GreenhouseController::logStartup(bool envOk, bool actuatorOk) const {
    Serial.print(F("[gh] begin env="));
    Serial.print(boolString(envOk));
    Serial.print(F(" actuator="));
    Serial.print(boolString(actuatorOk));
    Serial.print(F(" publish="));
    Serial.print(boolString(publisher_.isEnabled()));
    Serial.print(F(" wifi="));
    Serial.print(boolString(publisher_.isConnected()));
    Serial.print(F(" output_i2c=0x"));
    Serial.println(kOutputHubI2cAddress, HEX);
}

void GreenhouseController::logPumpStart(uint8_t index) const {
    Serial.print(F("[gh] pump start pot="));
    Serial.print(kPots[index].id);
    Serial.print(F(" channel="));
    Serial.print(kPots[index].outputChannel);
    Serial.print(F(" duration_ms="));
    Serial.print(pots_[index].pumpDurationMs);
    Serial.print(F(" moisture_pct="));
    Serial.println(pots_[index].moisturePercent, 1);
}

void GreenhouseController::logPumpStop(uint8_t index) const {
    Serial.print(F("[gh] pump stop pot="));
    Serial.print(kPots[index].id);
    Serial.print(F(" total_waterings="));
    Serial.println(pots_[index].totalWaterings);
}

void GreenhouseController::logPublishAttempt(bool ok, uint16_t statusCode) const {
    Serial.print(F("[gh] publish ok="));
    Serial.print(boolString(ok));
    Serial.print(F(" status="));
    Serial.print(statusCode);
    Serial.print(F(" queue="));
    Serial.println(queueCount_);
}

void GreenhouseController::logRuntimeSummary() const {
    Serial.print(F("[gh] state temp_c="));
    Serial.print(environment_.airTempC, 1);
    Serial.print(F(" humidity_pct="));
    Serial.print(environment_.airHumidityPct, 1);
    Serial.print(F(" co2_ppm="));
    Serial.print(environment_.co2Ppm);
    Serial.print(F(" active_pot="));
    Serial.print(activePotId());
    Serial.print(F(" queue="));
    Serial.print(queueCount_);
    Serial.print(F(" wifi="));
    Serial.print(boolString(publisher_.isConnected()));
    Serial.print(F(" alarms="));
    Serial.print(boolString(alarms_.environmentSensorFault));
    Serial.print('/');
    Serial.print(boolString(alarms_.anyMoistureFault));
    Serial.print('/');
    Serial.println(boolString(alarms_.wifiDisconnected));
}

const char* GreenhouseController::activePotId() const {
    return activePumpIndex_ >= 0 ? kPots[activePumpIndex_].id : "-";
}

}  // namespace greenhouse
