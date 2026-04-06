# BOM

## 部品表

| 区分 | 商品 | 数量 | 購入先 | 備考 |
| --- | --- | ---: | --- | --- |
| 制御基板 | Raspberry Pi Pico 2 WH | 1 | Switch Science | ヘッダ実装済み |
| 制御基板 | Robo Pico | 1 | Switch Science | 制御ベース |
| 温湿度 | Grove - Temperature & Humidity Sensor(SHT41) | 1 | Seeed Studio | 温室上部 |
| CO2 | Grove - SCD41搭載 CO2/温度/湿度センサ | 1 | Switch Science | 温室上部 |
| 土壌水分 | Gravity - 防水容量性土壌水分量センサ | 6 | Switch Science | 6鉢分 |
| 水分入力ハブ | MCP3008 A/Dコンバータ ピッチ変換済みモジュール | 1 | Switch Science | 8入力 |
| 出力ハブ | STEMMA QT/Qwiic互換 I2C 8chソレノイドドライバ | 1 | Switch Science | ポンプ6 + ファン2 |
| I2C変換 | Conta™ STEMMA QT/Qwiic用アダプター | 1 | Switch Science | 出力ハブ接続用 |
| ポンプ | Adafruit 1150 | 6 | DigiKey Japan | 12V、200-300mA、6鉢分 |
| 循環ファン | 12V ブラシレスファン 80mmクラス | 2 | 近場調達 | 上段/下段用 |
| 制御電源 | 5V/3.0A USB Micro-B ACアダプター | 1 | Switch Science | Pico / センサー用 |
| 駆動電源 | ACアダプター 12V/5A（ACコード付） | 1 | Switch Science | ポンプ / ファン用 |
| 書き込み用ケーブル | USB2.0ケーブル(A-microBタイプ)50cm | 1 | Switch Science | Pico 書き込み用 |
| Groveケーブル | GROVE - 4ピンケーブル 20cm (5本セット) | 1 | Switch Science | 環境センサー用 |
| センサー配線 | センサー延長線材 | 6本分 | 近場調達 | 上段3本、下段3本で束ねる |
| チューブ | 液体用シリコンチューブ | 3m 以上 | Switch Science など | 6鉢へ分岐なしで配る |
| 温室 | スリム温室4段 AS-SMO4 | 1 | ホームセンター系 | 約幅50 x 奥行45 x 高さ130cm |
| タンク | 5L前後のフタ付き容器 | 1 | 近場調達 | 温室外に配置 |
| 固定材 | 結束バンド、粘着固定具、ケーブルスリーブ | 適量 | 近場調達 | 棚ごとの束管理用 |

## 購入先ごとの分け方

### Switch Science

- `Raspberry Pi Pico 2 WH`
- `Robo Pico`
- `Grove - SCD41搭載 CO2/温度/湿度センサ`
- `Gravity - 防水容量性土壌水分量センサ` x6
- `MCP3008 A/Dコンバータ ピッチ変換済みモジュール`
- `STEMMA QT/Qwiic互換 I2C 8chソレノイドドライバ`
- `Conta™ STEMMA QT/Qwiic用アダプター`
- `5V/3.0A USB Micro-B ACアダプター`
- `ACアダプター 12V/5A（ACコード付）`
- `USB2.0ケーブル(A-microBタイプ)50cm`
- `GROVE - 4ピンケーブル 20cm (5本セット)`

### Seeed Studio

- `Grove - Temperature & Humidity Sensor(SHT41)` x1

### DigiKey Japan

- `Adafruit 1150` x6

### ホームセンター系

- `12V ブラシレスファン 80mmクラス` x2
- `スリム温室4段 AS-SMO4`
- `5L前後のフタ付き容器`
- `結束バンド`
- `粘着固定具`
- `ケーブルスリーブ`
- `シリコンチューブ`

## 購入メモ

- 6鉢では `出力を6個の単体リレーで持つ` より `8ch出力ハブ 1枚` の方が保守しやすい。
- 6鉢では `PicoのADC直結` では足りないので、`MCP3008` を前提にする。
- 電源は `5V logic` と `12V actuator` に分ける。
- `GND` は共通化する。
- `Adafruit 1150` は公開PDF上で `12VDC / 200-300mA`。

## 参考情報

- [Raspberry Pi Pico 2 WH](https://www.switch-science.com/products/10258)
- [Robo Pico](https://www.switch-science.com/products/9464)
- [Grove - Temperature & Humidity Sensor(SHT41)](https://www.seeedstudio.com/Grove-Temp-Humi-Sensor-SHT41-p-5383.html)
- [Grove - SCD41搭載 CO2/温度/湿度センサ](https://www.switch-science.com/products/7436/)
- [Gravity - 防水容量性土壌水分量センサ](https://www.switch-science.com/products/8104)
- [MCP3008 A/Dコンバータ ピッチ変換済みモジュール](https://www.switch-science.com/products/2023/)
- [STEMMA QT/Qwiic互換 I2C 8chソレノイドドライバ](https://www.switch-science.com/products/10395)
- [Conta™ STEMMA QT/Qwiic用アダプター](https://www.switch-science.com/products/9959)
- [1150 Adafruit Industries LLC | DigiKey Japan](https://www.digikey.jp/ja/products/detail/adafruit-industries-llc/1150/1528-1404-ND)
- [Adafruit 1150 PDF](https://www.mouser.com/datasheet/2/737/adafruit_1150_Web-3314762.pdf)
- [5V/3.0A USB Micro-B ACアダプター](https://www.switch-science.com/products/2801)
- [ACアダプター 12V/5A（ACコード付）](https://www.switch-science.com/products/9166)
- [USB2.0ケーブル(A-microBタイプ)50cm](https://www.switch-science.com/products/1035)
- [GROVE - 4ピンケーブル 20cm (5本セット)](https://www.switch-science.com/products/798)
- [武田コーポレーション スリム温室4段 AS-SMO4](https://item.rakuten.co.jp/yamakishi/39772169/)
