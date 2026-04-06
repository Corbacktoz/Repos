# Guide d'assemblage / Assembly Guide

## Prérequis

- Fer à souder + étain (ou fils Dupont pour prototypage)
- Arduino IDE avec le board package ESP32 installé
- Librairies Arduino : `VL53L1X` (Pololu), `NimBLE-Arduino`
- Câble USB-C

## Étape 1 : Câblage

Connecter le VL53L1X au XIAO ESP32-S3 selon le [schéma de câblage](wiring.md).

Pour le prototypage, des fils Dupont suffisent. Pour la version finale, souder directement les fils.

```
XIAO GPIO6 (SDA)  →  VL53L1X SDA
XIAO GPIO7 (SCL)  →  VL53L1X SCL
XIAO GPIO2        →  VL53L1X XSHUT
XIAO 3V3          →  VL53L1X VIN
XIAO GND          →  VL53L1X GND
```

## Étape 2 : Alimentation

1. Souder le fil (+) du support de piles au interrupteur SK12D07
2. Souder l'autre patte de l'interrupteur au pin **BAT** du XIAO
3. Souder le fil (−) du support de piles au pin **GND** du XIAO

⚠️ Vérifier la polarité avant d'insérer les piles.

## Étape 3 : Flash du firmware

1. Ouvrir Arduino IDE
2. Installer le board package **ESP32** (par Espressif) via le Board Manager
3. Sélectionner la carte : **XIAO_ESP32S3**
4. Installer les librairies via Library Manager :
   - **VL53L1X** par Pololu
   - **NimBLE-Arduino** par h2zero
5. Ouvrir `firmware/repos_firmware.ino`
6. Connecter le XIAO en USB-C
7. Compiler et téléverser

## Étape 4 : Test

1. Ouvrir le moniteur série (115200 baud)
2. Vérifier les messages :
   ```
   === REPOS v0.1 — XIAO ESP32-S3 ===
   [LIDAR] OFF
   [BLE] Advertising as 'REPOS'
   ```
3. Ouvrir `app/index.html` dans Chrome sur un smartphone
4. Cliquer "Connecter" → sélectionner "REPOS"
5. Cliquer "▶ Démarrer"
6. Passer la main au-dessus du capteur à moins de 70mm → le compteur doit incrémenter

## Étape 5 : Assemblage dans le boîtier

1. Percer un trou dans le couvercle du boîtier pour le capteur VL53L1X (fenêtre optique vers le haut)
2. Percer un trou latéral pour l'interrupteur SK12D07
3. Optionnel : percer un trou pour accès USB-C (mise à jour firmware)
4. Fixer les composants avec de la colle chaude ou des vis M2
5. Le capteur doit être orienté **face vers le haut** (fenêtre optique dégagée)

## Utilisation

1. Allumer l'interrupteur
2. Poser le boîtier au sol, capteur vers le haut
3. Se positionner au-dessus (pompes, squats, dips...)
4. Ouvrir l'app web sur le téléphone
5. Connecter → Régler les paramètres → Démarrer
6. Le capteur s'allume et s'éteint automatiquement entre les séries
7. Éteindre l'interrupteur après l'entraînement
