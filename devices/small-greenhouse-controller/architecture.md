# Architecture

## Overview

- 1台の制御基板が温室全体の空気温湿度と CO2 を見て、換気・循環・温度制御を行う。
- 6鉢ぶんの土壌水分は外置きの `ADCハブ` で集約し、鉢ごとに個別判定する。
- 6系統の給水出力は外置きの `8chドライバ` に集約し、ポンプは温室外でまとめて保守できるようにする。
- 温室内に置くのは `センサー`, `鉢`, `ファン`, `チューブ` だけに絞る。
- 電源は `制御/センサ系 5V` と `アクチュエータ系 12V` に分け、`GND` だけ共通にする。
- データ共有は `SORACOM Arc` 越しに `Unified Endpoint` へ送り、`Harvest Data` に集約する。

## Main components

- 制御:
  - `Raspberry Pi Pico 2 WH`
  - `Robo Pico`
- 入力:
  - `Grove SHT41`
  - `Grove SCD41`
  - `DFRobot SEN0308 x6`
  - `MCP3008 8ch ADC`
- 出力:
  - `STEMMA QT/Qwiic互換 I2C 8chソレノイドドライバ`
  - `12V ペリスタポンプ x6`
  - `12V 循環ファン x2`
- 電源:
  - `5V/3A` 制御/センサ系
  - `12V/5A` アクチュエータ系

## Baseline component choice

- 制御基板は `Pico 2 WH + Robo Pico` を基準にする。
  - 根拠: Wi-Fi、Grove、Pico系の扱いやすさを残しつつ、環境センサーまわりを簡単にできる。
- 土壌水分入力は `MCP3008 A/Dコンバータ ピッチ変換済みモジュール` を基準にする。
  - 根拠: 8入力あるので 6鉢を1枚で収容でき、ADC不足を避けられる。[Switch Science](https://www.switch-science.com/products/2023/)
- 出力は `STEMMA QT/Qwiic互換 I2C 8chソレノイドドライバ` を基準にする。
  - 根拠: 1枚で `ポンプ6系統 + ファン2系統` を扱え、各チャネルは `1A未満`、負荷電源は `3〜24V` を使える。[Switch Science](https://www.switch-science.com/products/10395)
- 土壌水分センサーは `DFRobot SEN0308` を基準にする。
  - 根拠: IP65 の防水容量式で温室常設に向く。[Switch Science](https://www.switch-science.com/products/8104)
- 環境センサーは `Grove SHT41 + Grove SCD41` を基準にする。
  - 根拠: 温湿度と CO2 を分離して扱えるので制御ロジックを分けやすい。[Seeed SHT41](https://www.seeedstudio.com/Grove-Temp-Humi-Sensor-SHT41-p-5383.html) [Switch Science SCD41](https://www.switch-science.com/products/7436/)
- ポンプは `12V ペリスタポンプ` を 6台まとめて外置きする。
  - 根拠: 6系統になると 5V より 12V の方が配線電流を抑えやすく、サービスボックス化しやすい。
  - 第一候補: `Adafruit 1150`。[DigiKey Japan](https://www.digikey.jp/ja/products/detail/adafruit-industries-llc/1150/1528-1404-ND)
- アクチュエータ電源は `12V/5A` を基準にする。
  - 根拠: ポンプとファンを1本化しやすい。[Switch Science](https://www.switch-science.com/products/9166)

## Physical layout assumptions

- 温室は `上段3鉢 + 下段3鉢` の2段運用を基準にする。
- 上部中央に `CO2 + 温湿度センサー` をまとめる。
- 上段後方に `上段ファン`、下段後方に `下段ファン` を置く。
- 制御ボックスは温室外の上側に固定し、`Pico 2 WH`, `Robo Pico`, `MCP3008` を収める。
- サービスボックスは温室外の下側に固定し、`8chドライバ`, `ポンプ6台`, `12V電源`, `タンク` をまとめる。
- センサー線は左後方、チューブは右後方に寄せる。
- 鉢番号は `U1 U2 U3 / L1 L2 L3` で固定する。

## Data flow

1. 温湿度、CO2、6鉢ぶんの土壌水分を定期サンプリングする。
2. 温度制御ループが上段/下段ファンや加温の ON/OFF を判断する。
3. CO2/換気制御ループが循環ファンまたは換気の優先度を判断する。
4. 給水制御ループが鉢ごとの乾き具合と直近給水履歴を見て給水可否を判断する。
5. 給水時は対象鉢のポンプだけを一定時間駆動する。
6. 同時給水は行わず、1回に1鉢だけ動かす。
7. 値とイベントをローカルでまとめ、`Unified Endpoint` へ送信する。

## Related diagrams

- [diagrams/system-overview.md](./diagrams/system-overview.md)
- [diagrams/layout-and-cabling.md](./diagrams/layout-and-cabling.md)
- [hardware/component-options.md](./hardware/component-options.md)
- [software/control-notes.md](./software/control-notes.md)
