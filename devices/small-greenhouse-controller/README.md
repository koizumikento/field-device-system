# small-greenhouse-controller

## Summary

- What this device does: 小型温室の温度・湿度・CO2 と、6鉢ぶんの土壌水分を見ながら、鉢ごとに給水する。
- Current status: `6鉢対応` を前提に、配線と保守性を優先した構成ドラフト。

## Main docs

- [purpose.md](./purpose.md)
- [requirements.md](./requirements.md)
- [architecture.md](./architecture.md)
- [operations.md](./operations.md)
- [hardware/component-options.md](./hardware/component-options.md)
- [hardware/bom.md](./hardware/bom.md)
- [software/control-notes.md](./software/control-notes.md)
- [setup/prototype-plan.md](./setup/prototype-plan.md)
- [tests/validation-checklist.md](./tests/validation-checklist.md)
- [diagrams/system-overview.md](./diagrams/system-overview.md)
- [diagrams/layout-and-cabling.md](./diagrams/layout-and-cabling.md)

## Current direction

- 鉢数: `6鉢`
- 配置: `2段 x 3鉢`
- 制御基板: `Raspberry Pi Pico 2 WH + Robo Pico`
- 水分入力: `MCP3008` を使った `8ch ADCハブ`
- 出力: `I2C 8chソレノイドドライバ` で `Pump 1-6` と `ファン` を集約
- 給水: 温室外の `6連ポンプバンク`
- 電源: `制御/センサ系 5V` と `アクチュエータ系 12V`
- データ共有: `SORACOM Arc + Unified Endpoint + Harvest Data`

## Notes

- Key constraints: 高湿度、結露、散水飛沫、配線束、チューブ束。
- Open issues: 12Vポンプの最終型番、ファンの最終型番、タンク液面検知の追加有無。
