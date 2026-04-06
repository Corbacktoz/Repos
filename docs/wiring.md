# Câblage / Wiring

## Schéma

```
XIAO ESP32-S3          VL53L1X
─────────────          ───────
3V3 ──────────────────── VIN
GND ──────────────────── GND
GPIO6 (SDA) ──────────── SDA
GPIO7 (SCL) ──────────── SCL
GPIO2 ────────────────── XSHUT

Alimentation / Power:
3× AA NiMH (+) ── [SK12D07] ── BAT pin XIAO
3× AA NiMH (-) ────────────── GND XIAO
```

## Détails

### I2C (VL53L1X)

Le capteur VL53L1X communique en I2C à 400 kHz (Fast Mode).

| Signal | XIAO Pin | VL53L1X Pin | Notes |
|--------|----------|-------------|-------|
| SDA    | GPIO6    | SDA         | Pull-up 10kΩ intégré sur le breakout |
| SCL    | GPIO7    | SCL         | Pull-up 10kΩ intégré sur le breakout |
| XSHUT  | GPIO2    | XSHUT       | Contrôle ON/OFF du capteur |
| VCC    | 3V3      | VIN         | Alimentation 3.3V |
| GND    | GND      | GND         | Masse commune |

### XSHUT (contrôle d'alimentation)

La broche XSHUT permet de mettre le VL53L1X en hardware standby :

- **LOW** → capteur éteint (< 5 µA)
- **HIGH** → capteur actif (~20 mA en mesure continue)

Le firmware utilise XSHUT pour :
- Éteindre le capteur au démarrage
- L'allumer uniquement pendant les séries d'exercice
- L'éteindre pendant les pauses entre séries
- L'éteindre à la fin de l'entraînement

### Alimentation

3× piles AA NiMH (type Eneloop) en série = ~3.6V nominal.

Connectées au pin **BAT** du XIAO ESP32-S3 via un interrupteur glissière SK12D07.

Le XIAO intègre un régulateur qui accepte 3.0V à 4.2V sur le pin BAT.

**Autonomie estimée** :
- ESP32-S3 BLE actif : ~50 mA
- VL53L1X en mesure : ~20 mA
- VL53L1X en standby : ~5 µA
- Total actif : ~70 mA → ~30h avec Eneloop 2000mAh
- En veille (LiDAR off) : ~50 mA → ~40h
