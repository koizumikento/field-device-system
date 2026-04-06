#pragma once

#include "CompatLibraries.h"
#include "GreenhouseTypes.h"

namespace greenhouse {

class EnvironmentSensors {
  public:
    bool begin(TwoWire& wire);
    bool read(EnvironmentReadings& out);
    const String& lastError() const { return lastError_; }

  private:
    bool readSht(EnvironmentReadings& out);
    bool readScd(EnvironmentReadings& out);
    void setError(const __FlashStringHelper* prefix, uint16_t code);

    Sht4xDriver sht4x_;
    Scd4xDriver scd4x_;
    EnvironmentReadings lastReadings_;
    String lastError_;
    bool scdStarted_ = false;
};

}  // namespace greenhouse
