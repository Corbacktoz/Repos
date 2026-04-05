# REPOS 💪

**R**ep **E**valuation and **P**erformance **O**pen **S**ystem

> Un compteur de répétitions open source basé sur LiDAR, pour la musculation au poids de corps.  
> An open-source LiDAR-based rep counter for bodyweight strength training.

---

![License](https://img.shields.io/badge/license-GPL%20v3-blue)
![Hardware](https://img.shields.io/badge/hardware-CERN%20OHL%20v2-green)
![Platform](https://img.shields.io/badge/platform-ESP32--S3-red)
![Status](https://img.shields.io/badge/status-in%20development-orange)

---

## 🇫🇷 Français

### Qu'est-ce que REPOS ?

REPOS est un petit boîtier électronique posé au sol qui compte vos répétitions de musculation avec précision, grâce à un capteur LiDAR. Il se connecte à votre téléphone via Bluetooth Low Energy (BLE) et permet de stocker des programmes d'entraînement.

### Pourquoi le LiDAR ?

Contrairement aux accéléromètres (montres connectées), le LiDAR mesure une **distance réelle** entre le capteur et votre corps. Résultat : zéro faux positif, comptage fiable même sur les mouvements lents.

### Exercices supportés

- Pompes (push-ups)
- Squats
- Dips
- Fentes
- Et tout exercice qui rapproche le corps du sol...

### Matériel nécessaire

| Composant | Référence | Prix indicatif |
|---|---|---|
| Microcontrôleur | XIAO ESP32-S3 | ~8€ |
| Capteur LiDAR | VL53L1X breakout | ~5€ |
| Piles | 3× AA NiMH (ex: Eneloop) | ~6€ |
| Support piles | 3×AA | ~0,50€ |
| Boîtier | ABS 80×50×26mm | ~1,20€ |
| Interrupteur | SK12D07 glissière | ~0,30€ |
| **Total** | | **~21€** |

### Structure du repo

```
repos/
├── firmware/         # Code Arduino/ESP-IDF pour XIAO ESP32-S3
├── hardware/         # Schémas de câblage (KiCad)
├── app/              # Interface web BLE (PWA)
├── docs/             # Documentation technique
│   ├── wiring.md     # Schéma de câblage détaillé
│   ├── bom.md        # Liste des composants
│   └── assembly.md   # Guide d'assemblage
└── enclosure/        # Fichiers STL pour impression 3D (à venir)
```

### Licence

- **Firmware** : [GPL v3](LICENSE-GPL.txt)
- **Hardware** : [CERN OHL v2](LICENSE-CERN-OHL.txt)
- **Documentation** : [CC BY-SA 4.0](LICENSE-CC.txt)

---

## 🇬🇧 English

### What is REPOS?

REPOS is a small electronic device placed on the floor that accurately counts your bodyweight exercise repetitions using a LiDAR sensor. It connects to your phone via Bluetooth Low Energy (BLE) and can store workout programs.

### Why LiDAR?

Unlike accelerometers (smartwatches), LiDAR measures an **actual distance** between the sensor and your body. The result: zero false positives, reliable counting even on slow movements.

### Supported exercises

- Push-ups
- Squats
- Dips
- Lunges
- Any exercise that brings the body closer to the floor...

### Bill of Materials

| Component | Reference | Approx. price |
|---|---|---|
| Microcontroller | XIAO ESP32-S3 | ~€8 |
| LiDAR sensor | VL53L1X breakout | ~€5 |
| Batteries | 3× AA NiMH (e.g. Eneloop) | ~€6 |
| Battery holder | 3×AA | ~€0.50 |
| Enclosure | ABS 80×50×26mm | ~€1.20 |
| Switch | SK12D07 slide switch | ~€0.30 |
| **Total** | | **~€21** |

### Repository structure

```
repos/
├── firmware/         # Arduino/ESP-IDF code for XIAO ESP32-S3
├── hardware/         # Wiring schematics (KiCad)
├── app/              # BLE web interface (PWA)
├── docs/             # Technical documentation
│   ├── wiring.md     # Detailed wiring diagram
│   ├── bom.md        # Bill of materials
│   └── assembly.md   # Assembly guide
└── enclosure/        # STL files for 3D printing (coming soon)
```

### License

- **Firmware**: [GPL v3](LICENSE-GPL.txt)
- **Hardware**: [CERN OHL v2](LICENSE-CERN-OHL.txt)
- **Documentation**: [CC BY-SA 4.0](LICENSE-CC.txt)

---

## 📡 Wiring / Câblage

```
XIAO ESP32-S3          VL53L1X
─────────────          ───────
3V3 ──────────────────── VIN
GND ──────────────────── GND
GPIO6 (SDA) ──────────── SDA
GPIO7 (SCL) ──────────── SCL
GPIO2 ────────────────── XSHUT

Power:
3× AA NiMH (+) ── [SW] ── BAT pin XIAO
3× AA NiMH (-) ────────── GND XIAO
```

---

## 🚧 Roadmap

- [x] Hardware design
- [x] Wiring diagram
- [ ] Firmware v0.1 — basic rep counting
- [ ] BLE GATT service
- [ ] Workout program storage
- [ ] PWA mobile interface
- [ ] 3D printable enclosure
- [ ] Multi-exercise calibration

---

## 🤝 Contributing / Contribuer

Contributions welcome! Open an issue or a pull request.  
Les contributions sont les bienvenues ! Ouvrez une issue ou une pull request.

---

## ✍️ Author / Auteur

Projet initié par un formateur avionique toulousain passionné d'électronique embarquée.  
Project initiated by an avionics trainer from Toulouse with a passion for embedded electronics.
