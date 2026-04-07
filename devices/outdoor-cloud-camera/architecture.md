# Architecture

## Overview

- 屋外対応カメラ、交換式バッテリー、LTE ルーター、取付金具を組み合わせる。

## Main components

- Device: `ATOM Cam Swing`
- Sensors or actuators: 追加センサーやアクチュエータは持たない
- Communication: `+F FS045W + 楽天モバイル Rakuten最強プラン`
- External systems: ソラカメのクラウド録画ライセンス、ユーザーコンソール、スマホアプリ、`+F FS045W`

## Data flow

1. `ATOM Cam Swing` が現地映像を取得する
2. 映像を `+F FS045W` 経由でソラカメへ送信する
3. 利用者がアプリまたはユーザーコンソールから視聴する

## Related diagrams

- [diagrams/power-and-wiring.md](./diagrams/power-and-wiring.md)
