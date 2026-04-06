#pragma once

#include "CompatLibraries.h"
#include "GreenhouseConfig.h"

namespace greenhouse {

class ActuatorHub {
  public:
    bool begin(TwoWire& wire);
    void allOff();
    void setChannel(uint8_t channel, bool enabled);
    bool isChannelEnabled(uint8_t channel) const;
    const String& lastError() const { return lastError_; }

  private:
    Adafruit_MCP23X17 io_;
    bool states_[kOutputChannelCount] = {false, false, false, false, false, false, false, false};
    String lastError_;
};

}  // namespace greenhouse
