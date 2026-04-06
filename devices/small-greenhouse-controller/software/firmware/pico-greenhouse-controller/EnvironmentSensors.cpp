#include "EnvironmentSensors.h"

namespace greenhouse {

bool EnvironmentSensors::begin(TwoWire& wire) {
    sht4x_.begin(wire);
    scd4x_.begin(wire);

    uint16_t error = scd4x_.stopPeriodicMeasurement();
    if (error != 0) {
        // ignore: the sensor may not be in periodic mode yet.
    }
    delay(20);

    error = scd4x_.startPeriodicMeasurement();
    if (error != 0) {
        setError(F("SCD4x start"), error);
        return false;
    }

    scdStarted_ = true;
    return true;
}

bool EnvironmentSensors::read(EnvironmentReadings& out) {
    out = lastReadings_;

    const bool shtOk = readSht(out);
    const bool scdOk = readScd(out);

    out.measuredAtMs = millis();
    lastReadings_ = out;
    return shtOk || scdOk;
}

bool EnvironmentSensors::readSht(EnvironmentReadings& out) {
    float temperature = NAN;
    float humidity = NAN;

    const uint16_t error = sht4x_.measureHighPrecision(temperature, humidity);
    if (error != 0) {
        out.shtOk = false;
        setError(F("SHT4x read"), error);
        return false;
    }

    out.airTempC = temperature;
    out.airHumidityPct = humidity;
    out.shtOk = true;
    return true;
}

bool EnvironmentSensors::readScd(EnvironmentReadings& out) {
    if (!scdStarted_) {
        out.scdOk = false;
        return false;
    }

    uint16_t dataReady = 0;
    uint16_t error = scd4x_.getDataReadyStatus(dataReady);
    if (error != 0) {
        out.scdOk = false;
        setError(F("SCD4x ready"), error);
        return false;
    }

    if (dataReady == 0) {
        out.scdFresh = false;
        return out.scdOk;
    }

    uint16_t co2 = 0;
    float temperature = NAN;
    float humidity = NAN;
    error = scd4x_.readMeasurement(co2, temperature, humidity);
    if (error != 0) {
        out.scdOk = false;
        setError(F("SCD4x read"), error);
        return false;
    }

    out.co2Ppm = co2;
    out.scdTempC = temperature;
    out.scdHumidityPct = humidity;
    out.scdOk = true;
    out.scdFresh = true;

    if (!out.shtOk) {
        out.airTempC = temperature;
        out.airHumidityPct = humidity;
    }

    return true;
}

void EnvironmentSensors::setError(const __FlashStringHelper* prefix, uint16_t code) {
    lastError_.remove(0);
    lastError_.reserve(48);
    lastError_ += prefix;
    lastError_ += ':';
    lastError_ += ' ';
    lastError_ += String(code);
}

}  // namespace greenhouse
