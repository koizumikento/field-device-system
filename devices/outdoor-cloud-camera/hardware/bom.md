# BOM

## 前提

- この BOM は `ソラカメ屋外スターターキットを使わない` 前提でまとめる。
- 標準構成は `+F FS045W + SIM`、`細いポール固定`、`カメラ直下に箱配置`、`7日交換 + 予備1本` とする。
- `積雪` と `直射日光` を考慮して、蓄電池は `12.8V 120Ah LiFePO4` を採用する。

## 部品表

### 標準構成: LTE + 交換式バッテリー運用

| 区分 | 商品 | 数量 | 購入先 | 備考 |
| --- | --- | ---: | --- | --- |
| カメラ | [ソラカメ対応製品] ATOM Cam Swing + ライセンス | 1 | SORACOM IoT ストア | `5V / 2A`、`IP65` |
| LTE ルーター | [+F FS045W `FS045WMB1`](https://fsi-plusf.jp/products/FS045W/) | 1 | 富士ソフト / 販売店 | 標準採用 |
| SIM | [動作確認済 SIM 一覧](https://fsi-plusf.jp/confirmed/) にある nanoSIM または eSIM | 1 | 回線事業者 | 事業者と APN は別途確定 |
| 蓄電池 | `12.8V 120Ah LiFePO4` | 2 | 別調達 | 使用中 1 本 + 予備 1 本 |
| 5V 変換 | [Blue Sea Systems 1045 12/24V Dual USB Charger 4.8A](https://www.bluesea.com/products/1045) | 1 | 別調達 | カメラと FS045W を同時給電 |
| 主ヒューズホルダ | [Blue Sea Systems 5061 Waterproof In-Line AGC/MDL Fuse Holder](https://www.bluesea.com/products/5061/Waterproof_In-Line_AGC_MDL_Fuse_Holder) | 1 | 別調達 | バッテリー正極の近く |
| 主ヒューズ | [Blue Sea Systems 5215 AGC Fuse 10A](https://www.bluesea.com/products/5215/AGC_Fuse_-_10_Amp) | 1 | 別調達 | 一次側保護 |
| 電装収納箱 | [タカチ WP20-28-7G](https://stage.takachi-el.co.jp/products/WP-P) | 1 | タカチ電機工業 / 販売店 | `IP67` |
| USB ケーブルシール | [Scanstrut DS16-P-BLK](https://www.scanstrut.com/uk/off-road/cable-seal/vertical/ds16-p) | 1 | 別調達 | 成端済み USB ケーブルを箱外へ出す |
| バッテリー箱 | [NOCO BG31 Snap-Top Battery Box](https://no.co/support/BG31/) | 2 | 別調達 | 使用中 1 箱 + 予備 1 箱 |
| 取付金具 | [RAM Mounts RAM-B-108B-A-366U](https://rammount.com/products/ram-b-108b-a-366u) | 1 | 別調達 | 細いポール固定の標準採用 |
| 固定材 | ステンレスバンド、耐候結束バンド、簡易遮熱板 | 1式 | 近場調達 | 細いポール固定 + 直射日光対策 |
| 配線 | `1.25sq〜2sq` 2芯ケーブル、M8圧着端子 | 1式 | 近場調達 | バッテリー箱から電装箱までの DC 配線 |
| 着脱コネクタ | [Anderson Powerpole PP15/45](https://www.andersonpower.com/us/en/category.html/wire-to-wire/powerpole/powerpole-15-45.html) | 1式 | 別調達 | 電装箱内のサービス切り離し用 |

## 追加オプション

### ネットワークを別調達する場合

| 区分 | 商品 | 数量 | 購入先 | 備考 |
| --- | --- | ---: | --- | --- |
| 通信 | [+F FS045W `FS045WMB1`](https://fsi-plusf.jp/products/FS045W/) | 0-1 | 富士ソフト / 販売店 | 第一候補として選定。`nanoSIM + eSIM`、`20時間`、`2.4/5GHz Wi-Fi`、最大 `15台` |
| 通信 | [動作確認済 SIM 一覧](https://fsi-plusf.jp/confirmed/) にある nanoSIM または eSIM | 0-1 | 回線事業者 | 契約プランに合わせて選定 |
| 通信オプション | [+F 充電/LANステーション `CLS001`](https://fsi-plusf.jp/products/option/lan_station/index.html) | 0-1 | 富士ソフト / 販売店 | 将来 `据え置き` や `バッテリーレス` に寄せる場合の拡張用 |
| 保護 | ルーター収納用防水ボックス | 0-1 | 別調達 | ルーターを電装箱と分けて屋外設置する場合のみ |

### LTE ルーター選定結果

- 選定機種は `+F FS045W`
- 選定理由:
  - 現行の 4G モバイルルーター製品
  - `nanoSIM + eSIM` のデュアル SIM 構成
  - `20時間` の連続通信
  - `2.4GHz/5GHz Wi-Fi`、最大 `15台` 接続
  - オプションの `+F 充電/LANステーション` を使うと、将来 `バッテリーレスで365日・24時間` の据え置き運用へ寄せられる
  - ユーザーガイド上の 4G 対応バンドが広く、日本国内の主要 LTE バンド `B1/B3/B8/B18/B19/B26/B28/B41` を含む
- 今回 `FS040W` ではなく `FS045W` を選んだのは、より新しく、`eSIM` と `バッテリーレス運用` の逃げ道があるため

### LTE を入れた場合の電力メモ

- このドキュメントでは、電源計算の基準は `4W` に固定する
- 理由は、SORACOM が屋外ソーラーキットで `ソラカメ + 通信用ドングル接続による常時録画` を `約4W` として扱っているため
- したがって、`ATOM Cam Swing + FS045W` 構成でも、まずは `システム負荷 4W` を基準設計値とする
- `FS045W` 単体の消費電力推定は補助情報に留め、容量計算の主値には使わない
- ただし今回は `積雪` と `直射日光`、`7日交換`、`予備1本` の運用余裕を見て、採用品は `120Ah`

### 独立電源化する場合

| 区分 | 商品 | 数量 | 購入先 | 備考 |
| --- | --- | ---: | --- | --- |
| 電源 | バッテリー、充電制御、DC-DC 変換、発電手段 | 別設計 | 別調達 | 現地の日照、必要稼働時間、通信方式に応じて別設計 |

### バッテリーのみで 7 日間運用する場合

| 区分 | 商品 | 数量 | 購入先 | 備考 |
| --- | --- | ---: | --- | --- |
| 蓄電池 | 12.8V 120Ah クラス `LiFePO4` | 1 | 別調達 | 採用。`4W` 設計基準に環境余裕を乗せる |
| 電源変換 | 12V -> 5V DC-DC コンバータ `5V / 3A` 以上 | 1 | 別調達 | カメラ給電用。変換損失を見込んで余裕を持たせる |
| 保護 | ヒューズ、バッテリーモニタ | 1式 | 別調達 | 過電流保護と残量管理用 |
| 収納 | 防雨・防滴バッテリーボックス | 1 | 別調達 | 結露、浸水、直射日光対策を含む |

### 具体 BOM 例: 7 日間 / ソーラーなし / LTE / 1 台運用

#### 最小構成

| 区分 | 型番・商品 | 数量 | 購入先 | 備考 |
| --- | --- | ---: | --- | --- |
| カメラ | [ソラカメ対応製品] ATOM Cam Swing + ライセンス | 1 | SORACOM IoT ストア | カメラ本体。`FS045W` に Wi-Fi 接続する |
| 長尺電源ケーブル | [USBケーブル 4.5m](https://www.atomtech.co.jp/products/atom-cam-usb-cable) | 1 | ATOM Tech | バッテリーボックスや制御箱を少し離して置けるよう、今回は入れておく |
| LTE ルーター | [+F FS045W `FS045WMB1`](https://fsi-plusf.jp/products/FS045W/) | 1 | 富士ソフト / 販売店 | 標準採用 |
| 回線 | [動作確認済 SIM 一覧](https://fsi-plusf.jp/confirmed/) にある nanoSIM または eSIM | 1 | 回線事業者 | 要確定 |
| 蓄電池 | `12.8V 120Ah LiFePO4` | 1 | 別調達 | 現場搭載分 |
| 5V 変換 | [Blue Sea Systems 1045 12/24V Dual USB Charger 4.8A](https://www.bluesea.com/products/1045) | 1 | 別調達 | `12V -> 5V USB` 変換を兼ねる。`4.8A total`、`IP45`、パネル穴加工前提 |
| 主ヒューズホルダ | [Blue Sea Systems 5061 Waterproof In-Line AGC/MDL Fuse Holder](https://www.bluesea.com/products/5061/Waterproof_In-Line_AGC_MDL_Fuse_Holder) | 1 | 別調達 | バッテリー正極の近くに入れる |
| 主ヒューズ | [Blue Sea Systems 5215 AGC Fuse 10A](https://www.bluesea.com/products/5215/AGC_Fuse_-_10_Amp) | 1 | 別調達 | この構成の一次側保護用 |
| 電装収納箱 | [タカチ WP20-28-7G](https://stage.takachi-el.co.jp/products/WP-P) | 1 | タカチ電機工業 / 販売店 | `ASA樹脂`、`IP67`、標準価格税別 `3,960円` |
| USB ケーブルシール | [Scanstrut DS16-P-BLK](https://www.scanstrut.com/uk/off-road/cable-seal/vertical/ds16-p) | 1 | 別調達 | `IP68`。`2〜8mm` 径ケーブル対応。`USB` のような成端済みケーブルを箱外へ出す用途 |
| バッテリー箱 | [NOCO BG31 Snap-Top Battery Box](https://no.co/support/BG31/) | 1 | 別調達 | Group `24-31` 対応。国内入手性が悪ければ同等の `Group 31 対応箱` に置換可 |
| 取付金具 | [RAM Mounts RAM-B-108B-A-366U](https://rammount.com/products/ram-b-108b-a-366u) | 1 | 別調達 | 細いポール固定の標準 |
| 固定材 | ステンレスバンド、耐候結束バンド、簡易遮熱板 | 1式 | 近場調達 | 細いポール固定 + 直射日光対策 |
| 配線 | `1.25sq〜2sq` 2芯ケーブル、M8圧着端子 | 1式 | 近場調達 | バッテリー箱から電装箱までの DC 配線用 |
| 着脱コネクタ | [Anderson Powerpole PP15/45](https://www.andersonpower.com/us/en/category.html/wire-to-wire/powerpole/powerpole-15-45.html) | 1式 | 別調達 | 電装箱内に収める `サービス切り離し用`。屋外露出はさせない |

#### 運用推奨追加

| 区分 | 型番・商品 | 数量 | 購入先 | 備考 |
| --- | --- | ---: | --- | --- |
| 充電器 | [Renogy 12V 20A AC-DC LiFePO4充電器 `RBC20A1P-JP`](https://jp.renogy.com/products/20a-ac-to-dc-lfp-portable-battery-charger) | 1 | Renogy JP | 週次の持ち帰り充電用。`IP65` |
| 残量計 | [Renogy RBM500 バッテリーモニター `RBM500-JP`](https://jp.renogy.com/en/products/renogy-battery-remote-meter) | 1 | Renogy JP | 電圧、電流、容量を確認できる |
| 予備蓄電池 | `12.8V 120Ah LiFePO4` | 1 | 別調達 | 予備 1 本を固定で持つ |

#### この BOM の考え方

- `12V系のバッテリー` から `5V USB` を作るところは、今回は `Blue Sea 1045` を使って簡素化する。
- `Pololu の裸基板型 DC-DC` でも組めるが、今回は `配線加工を減らす` 方を優先した。
- `予備蓄電池なし` でも 7 日運用は可能だが、充電中のダウンタイムが出る。
- 今回は `予備蓄電池 1 本あり` を前提にし、`1週間ごとに箱ごと交換` する。

#### LTE 運用へ切り替える差分

| 区分 | 型番・商品 | 数量 | 購入先 | 備考 |
| --- | --- | ---: | --- | --- |
| なし | なし | 0 | - | すでに標準構成へ織り込み済み |

- `Blue Sea 1045` は `Dual USB` なので、片側を `ATOM Cam Swing`、もう片側を `FS045W` に使う
- `FS045W` 本体は `WP20-28-7G` の中に同居させるより、電波状態を見ながら `別箱` に分ける方が調整しやすい

#### 具体 BOM の概算メモ

- `ATOM Cam Swing + ライセンス`: `5,680円`
- `USBケーブル 4.5m`: `980円`
- `12.8V 120Ah LiFePO4`: `別見積もり`
- `Renogy 12V 20A AC-DC LiFePO4充電器`: `15,999円`
- `Renogy RBM500`: `8,283円`
- `タカチ WP20-28-7G`: `3,960円` 税別
- `Blue Sea` と `NOCO` の国内価格は販売店差が大きいので別見積もり
- `Scanstrut DS16-P-BLK` と `Anderson Powerpole PP15/45` も販売店差が大きいので別見積もり

## 7 日間バッテリー運用の容量メモ

- まず切り分ける。
- `ATOM Cam Swing` 本体の公式仕様は `5V / 2000mA`。これは `必要な給電能力の上限` であって、常時消費電力が `10W` という意味ではない。
- 一方で SORACOM の屋外ソーラーキットは、`ソラカメ + 通信用ドングル接続による常時録画` を `約4W` 負荷として扱っている。
- したがって、`5V系のカメラ` を `12V系の蓄電池` で動かすこと自体は普通で、必要なのは `12V -> 5V` の DC-DC 変換だけ。
- バッテリー容量は `システム電圧` ではなく `平均消費電力 x 稼働時間` で決まる。12V で組んでも 24V で組んでも、必要 `Wh` は同じ。
- 今回の計算式は `必要バッテリーWh = 4W x 24時間 x 7日 / 0.9 x 1.2` とする。
- つまり `必要バッテリーWh = 約896Wh`。
- `12.8V系 LiFePO4` なら `896Wh / 12.8V / 0.8 = 約87.5Ah`。
- `12V系 AGM` なら `896Wh / 12V / 0.5 = 約149Ah`。

### 先に結論

- 採用値は `LiFePO4 12.8V 120Ah`
- `4W` 固定前提での最小基準は `LiFePO4 12.8V 100Ah`
- `AGM` を使うなら `12V 150Ah` 以上
- 今回は `積雪`、`直射日光`、`7日交換` の運用余裕を見て `120Ah` を選ぶ
- `5V / 2A` の `10W` は `平均負荷` ではなく `給電上限`

### 7 日間で必要な容量の見え方

| 見方 | 値 | 意味 |
| --- | ---: | --- |
| カメラの給電仕様上限 | `10W` | `5V x 2A`。平均負荷ではない |
| SORACOM のシステム負荷目安 | `約4W` | `ソラカメ + 通信用ドングル常時録画` |
| 設計計算に使う値 | `4W` | このドキュメントの固定前提 |
| 7日間の設計目安 | `約896Wh` | 変換損失と `20%` 予備を含む |

### 代表的なバッテリーサイズの目安

| 種別 | 公称容量 | 7 日間への適合感 | 備考 |
| --- | ---: | --- | --- |
| `LiFePO4` | `12.8V 100Ah` | 最小基準 | `4W` 固定前提なら成立 |
| `LiFePO4` | `12.8V 120Ah` | 採用 | 積雪、直射日光、交換余裕を考慮 |
| `AGM` | `12V 150Ah` | 最低ライン | 重量は増える |

### 今回の読み方

- `12V系か 5V系か` は `変換段の話` であって、必要容量計算の主語は `Wh`。
- カメラ本体は `5V系`。
- 蓄電池システムは `12V系` で組んでよい。
- その場合の必要容量は、`4W固定前提で 100Ah が最小基準`、`今回は 120Ah を採用` と読む。

## 蓄電池の選び方

### 第一候補

- `LiFePO4` が最有力。
- 理由は、同容量で軽く、サイクル寿命が長く、今回の `7日間` 条件では `100Ah から 120Ah` に収まりやすいから。
- 冬季に屋外で充電する可能性があるなら、`低温充電保護` または `自己加熱` 付きのモデルを優先する。

### 代替候補

- `AGM`
  - 初期費用を抑えやすく、構成は単純。
  - ただし重く、同じ用途で必要容量が増える。短期のバックアップ用途なら現実的。
- `LTO (SCiB など)`
  - 低温、寿命、安全性を最優先するなら強い。
  - ただし価格と実装難度が高く、この規模では過剰になりやすい。

## 購入メモ

- `ATOM Cam Swing` 自体は `IP65` だが、同梱の電源アダプタは防水非対応。屋外では `アダプタ本体` と `USB 接続部` の防雨対策が必要。
- `ATOM Cam Swing` は `1/4 インチ三脚ネジ方式` の別売りブラケットに対応している。固定金具は公式付属品ではないため別調達にする。
- `USBケーブル 4.5m` は純正品がある。屋外では延長接続点を増やさず、純正の長尺ケーブルを優先する。
- 独立電源を自作する場合は、`5V / 2A` は `給電上限`、`約4W` は `システム平均負荷の参考値` として別に扱う。
- このドキュメントでは、`4W` を `標準の設計基準値` として扱い、ケース分けはしない。
- `LiFePO4` の弱点は `低温時の充電`。冬季の屋外充電を考えるなら、`低温充電保護` または `自己加熱` 付きモデルが扱いやすい。
- `AGM` は重量が増えるが、`0°C 以上` の充電条件であれば扱いは素直。バックアップ運用でサイクル頻度が低いなら選択肢に残る。
- `LTO` は寒冷地や高信頼用途には魅力があるが、今回の 1 台構成では部材調達と実装難度が高い。

## 初期費用メモ

- `ATOM Cam Swing + クラウド録画ライセンス`: `5,680円`
- `ATOM Cam Swing 用 USBケーブル 4.5m`: `980円`
- 上記は `2026-04-07` 時点で確認した公式掲載価格。別調達のブラケット、防水ボックス、固定材、通信機器は別見積もり。

## 継続費用メモ

- `ソラカメ録画ライセンス`: `990円 / 月` から
- 別調達ルーターや別回線を使う場合は、通信費が別途かかる

## 要確認項目

- `SIM事業者` と `APN`
- `細いポール` の実寸
- `直射日光` をどこまで避けられるか
- 冬季に `0°C 未満` で充電が起こりうるか

## 参考情報

- [[ソラカメ対応製品] ATOM Cam Swing](https://soracom.jp/store/22020/)
- [ATOM Cam Swing 公式仕様](https://www.atomtech.co.jp/products/atomcamswing?segment=spec)
- [〖ATOM Cam2 / Swing〗屋外での設置方法について教えて下さい。](https://info.atomtech.co.jp/support/faq/1966/)
- [USBケーブル 4.5m](https://www.atomtech.co.jp/products/atom-cam-usb-cable)
- [三脚にも対応！ソラカメ対応カメラ「ATOM Cam」設置ノウハウ](https://blog.soracom.com/ja-jp/2023/06/26/sora-cam-installation/)
- [SORACOM 屋外ソーラーキット仕様](https://soracom.jp/store/32800/)
- [Renogy 12V 100Ah Pro LiFePO4](https://www.renogy.com/products/12v-100ah-pro-smart-lithium-iron-phosphate-battery-w-bluetooth-self-heating-function)
- [Renogy 12V 100Ah AGM](https://www.renogy.com/products/deep-cycle-agm-battery-12-volt-100ah)
- [Toshiba SCiB](https://www.global.toshiba/ww/products-solutions/battery/scib/about.html)
