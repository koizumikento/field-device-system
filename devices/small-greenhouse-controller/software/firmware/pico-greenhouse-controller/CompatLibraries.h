#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>

#if __has_include(<Adafruit_MCP23X17.h>)
#include <Adafruit_MCP23X17.h>
#else
#error "Adafruit_MCP23X17.h not found. Install the Adafruit MCP23X17 library."
#endif

#if __has_include(<SensirionI2CSht4x.h>)
#include <SensirionI2CSht4x.h>
using Sht4xDriver = SensirionI2CSht4x;
#elif __has_include(<SensirionI2cSht4x.h>)
#include <SensirionI2cSht4x.h>
using Sht4xDriver = SensirionI2cSht4x;
#else
#error "Sensirion I2C SHT4x library not found."
#endif

#if __has_include(<SensirionI2CScd4x.h>)
#include <SensirionI2CScd4x.h>
using Scd4xDriver = SensirionI2CScd4x;
#elif __has_include(<SensirionI2cScd4x.h>)
#include <SensirionI2cScd4x.h>
using Scd4xDriver = SensirionI2cScd4x;
#else
#error "Sensirion I2C SCD4x library not found."
#endif
