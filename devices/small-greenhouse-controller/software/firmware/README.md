# Firmware

## Target

- Board: `Raspberry Pi Pico 2 WH`
- Base: `Robo Pico`
- Runtime: `Arduino` on `arduino-pico`

## Sketch

- [pico-greenhouse-controller/pico_greenhouse_controller.ino](./pico-greenhouse-controller/pico_greenhouse_controller.ino)
- 主要設定: [pico-greenhouse-controller/GreenhouseConfig.h](./pico-greenhouse-controller/GreenhouseConfig.h)
- 制御本体: [pico-greenhouse-controller/GreenhouseController.cpp](./pico-greenhouse-controller/GreenhouseController.cpp)

## Required libraries

- `Sensirion I2C SHT4x`
- `Sensirion I2C SCD4x`
- `Adafruit MCP23X17`

## 現在のピン割り当て

- `I2C SDA`: `GP8`
- `I2C SCL`: `GP9`
- `SPI RX`: `GP16`
- `SPI CS`: `GP17`
- `SPI SCK`: `GP18`
- `SPI TX`: `GP19`

## 出力チャネル

- `0`: `pump_u1`
- `1`: `pump_u2`
- `2`: `pump_u3`
- `3`: `pump_l1`
- `4`: `pump_l2`
- `5`: `pump_l3`
- `6`: `fan_upper`
- `7`: `fan_lower`

## 実装メモ

- `GreenhouseConfig.h` に Wi-Fi、SORACOM 送信先、しきい値、鉢ごとの校正値を設定してから書き込む前提。
- `kWifiSsid` を空にすると、送信を無効化したローカル制御専用モードとして動く。
- `MCP3008` はライブラリに依存せず、SPI を直接叩く実装。
- `8chソレノイドドライバ` は `Adafruit MCP23X17` 互換として扱っている。
- シリアルには起動結果、ポンプ開始/停止、送信結果、30秒ごとの状態要約を出す。
- JSON には環境値、6鉢の水分、アクティブ鉢、送信キュー状態、送信成功/失敗回数を含める。
- このリポジトリ内ではビルド未検証。
