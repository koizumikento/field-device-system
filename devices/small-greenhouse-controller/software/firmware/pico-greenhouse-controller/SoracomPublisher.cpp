#include "SoracomPublisher.h"

namespace greenhouse {

void SoracomPublisher::begin() {
    enabled_ = strlen(kWifiSsid) > 0;
    if (!enabled_) {
        return;
    }
    WiFi.begin(kWifiSsid, kWifiPassword);
    lastConnectAttemptMs_ = millis();
}

void SoracomPublisher::tick() {
    if (isConnected()) {
        return;
    }

    const uint32_t now = millis();
    if (now - lastConnectAttemptMs_ < kWifiRetryIntervalMs) {
        return;
    }

    reconnect();
}

bool SoracomPublisher::publishJson(const String& payload, uint16_t& statusCode) {
    statusCode = 0;
    if (!enabled_) {
        return false;
    }
    tick();
    if (!isConnected()) {
        return false;
    }

    WiFiClient client;
    if (!client.connect(kSoracomHost, kSoracomPort)) {
        return false;
    }

    client.print(String(F("POST ")) + kSoracomPath + F(" HTTP/1.1\r\n"));
    client.print(String(F("Host: ")) + kSoracomHost + F("\r\n"));
    client.print(F("User-Agent: pico-greenhouse-controller/0.1\r\n"));
    client.print(F("Content-Type: application/json\r\n"));
    client.print(F("Connection: close\r\n"));
    client.print(String(F("Content-Length: ")) + payload.length() + F("\r\n\r\n"));
    client.print(payload);

    const uint32_t timeoutAt = millis() + 5000;
    while (!client.available() && millis() < timeoutAt) {
        delay(10);
    }

    if (!client.available()) {
        client.stop();
        return false;
    }

    const String statusLine = client.readStringUntil('\n');
    if (statusLine.startsWith(F("HTTP/1.1 "))) {
        statusCode = static_cast<uint16_t>(statusLine.substring(9, 12).toInt());
    }

    client.stop();
    return statusCode >= 200 && statusCode < 300;
}

bool SoracomPublisher::isConnected() const {
    return enabled_ && WiFi.status() == WL_CONNECTED;
}

long SoracomPublisher::rssi() const {
    return isConnected() ? WiFi.RSSI() : 0;
}

void SoracomPublisher::reconnect() {
    if (!enabled_) {
        return;
    }
    lastConnectAttemptMs_ = millis();
    WiFi.disconnect();
    WiFi.begin(kWifiSsid, kWifiPassword);
}

}  // namespace greenhouse
