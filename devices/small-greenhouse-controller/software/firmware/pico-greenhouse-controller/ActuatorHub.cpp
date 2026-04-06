#include "ActuatorHub.h"

namespace greenhouse {

bool ActuatorHub::begin(TwoWire& wire) {
    if (!io_.begin_I2C(kOutputHubI2cAddress, &wire)) {
        lastError_ = F("MCP23X17 init failed");
        return false;
    }

    for (uint8_t channel = 0; channel < kOutputChannelCount; ++channel) {
        io_.pinMode(channel, OUTPUT);
    }

    allOff();
    return true;
}

void ActuatorHub::allOff() {
    for (uint8_t channel = 0; channel < kOutputChannelCount; ++channel) {
        setChannel(channel, false);
    }
}

void ActuatorHub::setChannel(uint8_t channel, bool enabled) {
    if (channel >= kOutputChannelCount) {
        return;
    }

    states_[channel] = enabled;
    const bool level = kOutputActiveHigh ? enabled : !enabled;
    io_.digitalWrite(channel, level ? HIGH : LOW);
}

bool ActuatorHub::isChannelEnabled(uint8_t channel) const {
    if (channel >= kOutputChannelCount) {
        return false;
    }
    return states_[channel];
}

}  // namespace greenhouse
