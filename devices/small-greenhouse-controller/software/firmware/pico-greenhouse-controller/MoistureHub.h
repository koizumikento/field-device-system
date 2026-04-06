#pragma once

#include "CompatLibraries.h"
#include "GreenhouseConfig.h"

namespace greenhouse {

class MoistureHub {
  public:
    explicit MoistureHub(uint8_t chipSelectPin) : chipSelectPin_(chipSelectPin) {}

    void begin(SPIClass& spi);
    void readAll(PotState states[kPotCount]);

  private:
    uint16_t readChannel(uint8_t channel) const;
    static float normalizePercent(uint16_t raw, const PotConfig& config);

    SPIClass* spi_ = nullptr;
    uint8_t chipSelectPin_;
};

}  // namespace greenhouse
