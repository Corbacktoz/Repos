# Liste des composants / Bill of Materials

## Composants principaux

| # | Composant | Référence | Qté | Prix indicatif | Lien |
|---|-----------|-----------|-----|---------------|------|
| 1 | Microcontrôleur | Seeed XIAO ESP32-S3 | 1 | ~8€ | [Seeed Studio](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) |
| 2 | Capteur LiDAR | VL53L1X breakout (Pololu, GY-53L1X ou équivalent) | 1 | ~5€ | [AliExpress](https://aliexpress.com) / [Pololu](https://www.pololu.com/product/3415) |
| 3 | Piles rechargeables | AA NiMH 2000mAh (ex: Eneloop) | 3 | ~6€ | — |
| 4 | Support de piles | 3×AA avec fils | 1 | ~0,50€ | — |
| 5 | Boîtier | ABS 80×50×26mm | 1 | ~1,20€ | — |
| 6 | Interrupteur | SK12D07 glissière | 1 | ~0,30€ | — |

**Total : ~21€**

## Consommables

| Composant | Notes |
|-----------|-------|
| Fils Dupont ou fil de câblage | Pour les connexions internes |
| Colle chaude ou vis M2 | Fixation des composants dans le boîtier |

## Optionnel

| Composant | Référence | Notes |
|-----------|-----------|-------|
| Buzzer passif | 5V passif | Pour feedback sonore (non implémenté dans v0.1) |
| LED RGB | WS2812B | Pour indication visuelle d'état |
| Batterie LiPo | 3.7V 500mAh+ | Alternative aux piles AA, charge USB-C via le XIAO |

## Notes

- Le XIAO ESP32-S3 a un connecteur USB-C pour la programmation et le debug série
- Le breakout VL53L1X inclut les résistances pull-up I2C (10kΩ)
- Tout fonctionne en 3.3V, pas besoin de level shifter
