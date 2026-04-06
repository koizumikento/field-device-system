#include "MoistureHub.h"

namespace greenhouse {

void MoistureHub::begin(SPIClass& spi) {
    spi_ = &spi;

    pinMode(chipSelectPin_, OUTPUT);
    digitalWrite(chipSelectPin_, HIGH);
    spi_->begin();
}

void MoistureHub::readAll(PotState states[kPotCount]) {
    for (uint8_t i = 0; i < kPotCount; ++i) {
        const PotConfig& config = kPots[i];
        const uint16_t raw = readChannel(config.adcChannel);

        states[i].rawAdc = raw;
        states[i].sensorFault = raw <= 3 || raw >= 1020;
        states[i].moisturePercent = normalizePercent(raw, config);
    }
}

uint16_t MoistureHub::readChannel(uint8_t channel) const {
    if (spi_ == nullptr || channel > 7) {
        return 0;
    }

    SPISettings settings(kMcp3008SpiClockHz, MSBFIRST, SPI_MODE0);
    spi_->beginTransaction(settings);
    digitalWrite(chipSelectPin_, LOW);

    spi_->transfer(0x01);
    const uint8_t high = spi_->transfer(static_cast<uint8_t>((0x08 | channel) << 4));
    const uint8_t low = spi_->transfer(0x00);

    digitalWrite(chipSelectPin_, HIGH);
    spi_->endTransaction();

    return static_cast<uint16_t>(((high & 0x03) << 8) | low);
}

float MoistureHub::normalizePercent(uint16_t raw, const PotConfig& config) {
    const int32_t span = static_cast<int32_t>(config.adcWet) - static_cast<int32_t>(config.adcDry);
    if (span == 0) {
        return 0.0f;
    }

    const float percent =
        100.0f * (static_cast<float>(raw) - static_cast<float>(config.adcDry)) / static_cast<float>(span);
    return constrain(percent, 0.0f, 100.0f);
}

}  // namespace greenhouse
