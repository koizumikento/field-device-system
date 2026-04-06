# Component Options

## Baseline set

- 制御基板: `Raspberry Pi Pico 2 WH`
- 配線ベース: `Robo Pico`
- 温室本体: `約幅50 x 奥行45 x 高さ130 cm` のスリム温室
- 温湿度: `Grove - Temperature & Humidity Sensor (SHT41)`
- CO2: `Grove - SCD41搭載 CO2/温度/湿度センサ`
- 土壌水分: `DFRobot SEN0308 x6`
- 水分入力ハブ: `MCP3008 A/Dコンバータ ピッチ変換済みモジュール`
- 出力ハブ: `STEMMA QT/Qwiic互換 I2C 8chソレノイドドライバ`
- I2C変換: `Conta™ STEMMA QT/Qwiic用アダプター`
- 給水: `12V ペリスタポンプ x6`
- 送風/循環: `12V ブラシレスファン x2`
- 電源:
  - `制御/センサ系`: `5V 3A 以上`
  - `アクチュエータ系`: `12V 5A 以上`
- データ共有: `SORACOM Arc + Unified Endpoint + Harvest Data`

## Why this set

### 1. Controller

- `Pico 2 WH` は Wi-Fi を持ち、SORACOM Arc と相性がよい。
- `Robo Pico` は Grove 接続と Pico 周辺の配線整理に向く。
- 6鉢でも、アナログ入力と出力を外部ハブへ逃がせば制御基板は変えずに済む。

Reference:
- [Pico-series Microcontrollers](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html)
- [Robo Pico](https://my.cytron.io/p-robo-pico)

### 2. Moisture input hub

- `MCP3008` は `8ch` の SPI ADC なので、`SEN0308 x6` を1枚で受けられる。
- ADC を温室外へまとめることで、湿気のある側に変換基板を置かずに済む。
- 6本のセンサー線を `上段3本` と `下段3本` の2束に分けて裏面へ落とせる。

Reference:
- [MCP3008 A/Dコンバータ ピッチ変換済みモジュール](https://www.switch-science.com/products/2023/)

### 3. Actuator output hub

- `STEMMA QT/Qwiic互換 I2C 8chソレノイドドライバ` は、1枚で `8出力` を扱える。
- 6ポンプに加えて、上段/下段ファンも同じ箱に集約できる。
- 制御は I2C なので GPIO の本数を消費しにくい。
- 負荷電源が `3〜24V` なので、12Vアクチュエータ系と組み合わせやすい。
- `Conta™ STEMMA QT/Qwiic用アダプター` を使うと、Pico 側の I2C へ引き出しやすい。

Reference:
- [STEMMA QT/Qwiic互換 I2C 8chソレノイドドライバ](https://www.switch-science.com/products/10395)
- [Conta™ STEMMA QT/Qwiic用アダプター](https://www.switch-science.com/products/9959)

### 4. Environmental sensing

- `SHT41` は温湿度専用として扱いやすい。
- `SCD41` は CO2 と温室内の空気状態の把握に向く。
- 空気センサーは鉢ごとに増やさず、温室全体で1系統にまとめる方が保守しやすい。

Reference:
- [Grove - Temperature & Humidity Sensor(SHT41)](https://www.seeedstudio.com/Grove-Temp-Humi-Sensor-SHT41-p-5383.html)
- [Grove - SCD41搭載 CO2/温度/湿度センサ](https://www.switch-science.com/products/7436/)

### 5. Watering hardware

- 6鉢では `1鉢1ポンプ` のままでも、すべてを温室外のサービスボックスに集約すれば保守性は保てる。
- チューブは各鉢へ1本ずつ、ポンプ側は箱の中で番号管理する。
- 第一候補の `Adafruit 1150` は DigiKey Japan で流通している。

Reference:
- [1150 Adafruit Industries LLC | DigiKey Japan](https://www.digikey.jp/ja/products/detail/adafruit-industries-llc/1150/1528-1404-ND)

### 6. Power design

- 6鉢では `制御/センサ系 5V` と `アクチュエータ系 12V` を分けた方が素直。
- 12V 側はポンプとファンの共通バスにし、5V 側は Pico とセンサーに限定する。
- `GND` だけ共通化し、信号基準を合わせる。

Reference:
- [5V/3.0A USB Micro-B ACアダプター](https://www.switch-science.com/products/2801)
- [ACアダプター 12V/5A（ACコード付）](https://www.switch-science.com/products/9166)

## Layout and cabling notes

- 鉢配置は `U1 U2 U3 / L1 L2 L3` に固定する。
- `上段ハーネス` と `下段ハーネス` に分け、各束に `センサー3本 + チューブ3本` をまとめる。
- センサー線は左後方、チューブは右後方へ寄せる。
- 制御ボックスとサービスボックスは分け、ポンプ交換時に制御系へ触れなくてよいようにする。
- 同時給水は行わず、ポンプは逐次駆動にする。

## Practical recommendation

- 6鉢前提では、`Pico 2 WH + Robo Pico + SHT41 + SCD41 + SEN0308 x6 + MCP3008 x1 + I2C 8chソレノイドドライバ x1 + 12Vポンプ x6 + 12Vファン x2` を基準にする。
- `2鉢から増やす` 発想ではなく、最初から `6鉢の配線束と保守動線` を設計した方が後戻りが少ない。
- 先に `棚ごとの束ね方` と `サービスボックス位置` を決めてから、GPIO や I2C の割り当てを決める。
