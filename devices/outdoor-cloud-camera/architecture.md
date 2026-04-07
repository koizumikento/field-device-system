# Architecture

## Overview

- 屋外対応カメラ、電源保護、通信、取付金具を最小構成として組み合わせる。

## Main components

- Device: `ATOM Cam Swing`
- Sensors or actuators: 追加センサーやアクチュエータは持たない
- Communication: 既存の `2.4GHz Wi-Fi`。届かない場合は `+F FS045W` を追加
- External systems: ソラカメのクラウド録画ライセンス、ユーザーコンソール、スマホアプリ、必要に応じて `+F FS045W`

## Data flow

1. `ATOM Cam Swing` が現地映像を取得する
2. 映像を `2.4GHz Wi-Fi` または `+F FS045W` 経由でソラカメへ送信する
3. 利用者がアプリまたはユーザーコンソールから視聴する

## Related diagrams

- [diagrams/power-and-wiring.md](./diagrams/power-and-wiring.md)
