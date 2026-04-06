#pragma once

#include "CompatLibraries.h"
#include "GreenhouseConfig.h"

namespace greenhouse {

class SoracomPublisher {
  public:
    void begin();
    void tick();
    bool publishJson(const String& payload, uint16_t& statusCode);
    bool isConnected() const;
    bool isEnabled() const { return enabled_; }
    long rssi() const;

  private:
    void reconnect();

    bool enabled_ = false;
    uint32_t lastConnectAttemptMs_ = 0;
};

}  // namespace greenhouse
