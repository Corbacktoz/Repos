/*
 * REPOS — Rep Evaluation and Performance Open System
 * Firmware v0.1 for XIAO ESP32-S3 + VL53L1X + NimBLE
 * 
 * Wiring:
 *   - VL53L1X SDA   → GPIO6
 *   - VL53L1X SCL   → GPIO7
 *   - VL53L1X XSHUT → GPIO2
 *   - Power: 3×AA NiMH → BAT pin XIAO
 * 
 * License: GPL v3
 * https://github.com/Corbacktoz/Repos
 */

#include <Wire.h>
#include <VL53L1X.h>
#include <NimBLEDevice.h>

// === PINS ===
#define SDA_PIN   6
#define SCL_PIN   7
#define XSHUT_PIN 2

// === CONFIG ===
#define SEUIL_MM        70
#define DEBOUNCE_MS     400
#define TIMING_BUDGET   20000   // 20ms → 50 Hz
#define MEASURE_INTERVAL 20
#define PROFILE_BATCH   10

// === BLE UUIDs ===
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_COUNT_UUID     "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR_PROFILE_UUID   "d1a7e8b2-4c5f-6a3d-9e2b-1f8c7d4a5b6e"
#define CHAR_COMMAND_UUID   "1c95d5e3-d8f7-413a-bf3d-7a2e5d7be87e"

// === GLOBALS ===
VL53L1X sensor;
NimBLEServer* pServer = nullptr;
NimBLECharacteristic* pCountChar = nullptr;
NimBLECharacteristic* pProfileChar = nullptr;
NimBLECharacteristic* pCommandChar = nullptr;

uint16_t repCount = 0;
uint16_t totalCount = 0;
uint8_t  series = 1;
bool deviceConnected = false;
bool wasNear = false;
bool lidarActive = false;
unsigned long lastRepTime = 0;
unsigned long startTime = 0;

String profileBuffer = "";
int sampleCount = 0;

// === FORWARD DECLARATIONS ===
void sendCountData();
void sendProfileData(unsigned long timestamp, uint16_t distance);
void lidarOn();
void lidarOff();

// === LIDAR POWER ===
void lidarOff() {
  if (!lidarActive) return;
  sensor.stopContinuous();
  digitalWrite(XSHUT_PIN, LOW);
  lidarActive = false;
  Serial.println("[LIDAR] OFF");
}

void lidarOn() {
  if (lidarActive) return;
  digitalWrite(XSHUT_PIN, HIGH);
  delay(10);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);
  sensor.setTimeout(500);

  if (!sensor.init()) {
    Serial.println("[LIDAR] Init FAILED");
    return;
  }

  sensor.setDistanceMode(VL53L1X::Short);
  sensor.setMeasurementTimingBudget(TIMING_BUDGET);
  sensor.startContinuous(MEASURE_INTERVAL);
  lidarActive = true;
  Serial.println("[LIDAR] ON — 50 Hz");
}

// === BLE CALLBACKS ===
class ServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* server, NimBLEConnInfo& connInfo) {
    deviceConnected = true;
    startTime = millis();
    Serial.println("[BLE] Connected");
  }
  void onDisconnect(NimBLEServer* server, NimBLEConnInfo& connInfo, int reason) {
    deviceConnected = false;
    lidarOff();
    Serial.println("[BLE] Disconnected");
    NimBLEDevice::startAdvertising();
  }
};

class CommandCallbacks : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
    std::string cmd = pCharacteristic->getValue();
    Serial.printf("[CMD] %s\n", cmd.c_str());

    if (cmd == "START") {
      lidarOn();
    }
    else if (cmd == "PAUSE") {
      lidarOff();
    }
    else if (cmd == "RESET") {
      repCount = 0;
      totalCount = 0;
      series = 1;
      wasNear = false;
      startTime = millis();
      sendCountData();
      lidarOn();
    }
    else if (cmd == "SERIES") {
      repCount = 0;
      series++;
      wasNear = false;
      sendCountData();
      lidarOn();
    }
  }
};

// === BLE SEND ===
void sendCountData() {
  if (!deviceConnected) return;
  String data = String(repCount) + "," + String(totalCount) + "," + String(series);
  pCountChar->setValue(data.c_str());
  pCountChar->notify();
}

void sendProfileData(unsigned long timestamp, uint16_t distance) {
  if (!deviceConnected) return;

  unsigned long t = timestamp - startTime;
  if (profileBuffer.length() > 0) profileBuffer += "|";
  profileBuffer += String(t) + "," + String(distance);
  sampleCount++;

  if (sampleCount >= PROFILE_BATCH) {
    pProfileChar->setValue(profileBuffer.c_str());
    pProfileChar->notify();
    profileBuffer = "";
    sampleCount = 0;
  }
}

// === SETUP ===
void setup() {
  Serial.begin(115200);
  Serial.println("\n=== REPOS v0.1 — XIAO ESP32-S3 ===");

  // XSHUT: LiDAR off at boot
  pinMode(XSHUT_PIN, OUTPUT);
  digitalWrite(XSHUT_PIN, LOW);

  // I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);

  // NimBLE
  NimBLEDevice::init("REPOS");
  pServer = NimBLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  NimBLEService* pService = pServer->createService(SERVICE_UUID);

  pCountChar = pService->createCharacteristic(
    CHAR_COUNT_UUID,
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
  );

  pProfileChar = pService->createCharacteristic(
    CHAR_PROFILE_UUID,
    NIMBLE_PROPERTY::NOTIFY
  );

  pCommandChar = pService->createCharacteristic(
    CHAR_COMMAND_UUID,
    NIMBLE_PROPERTY::WRITE
  );
  pCommandChar->setCallbacks(new CommandCallbacks());

  pService->start();

  NimBLEAdvertising* pAdv = NimBLEDevice::getAdvertising();
  pAdv->addServiceUUID(SERVICE_UUID);
  pAdv->start();

  Serial.println("[BLE] Advertising as 'REPOS'");
  startTime = millis();
}

// === LOOP ===
void loop() {
  // NimBLE connection detection fallback
  if (pServer->getConnectedCount() > 0 && !deviceConnected) {
    deviceConnected = true;
    startTime = millis();
    Serial.println("[BLE] Connected (loop detect)");
  } else if (pServer->getConnectedCount() == 0 && deviceConnected) {
    deviceConnected = false;
    lidarOff();
    Serial.println("[BLE] Disconnected (loop detect)");
    NimBLEDevice::startAdvertising();
  }

  if (!lidarActive) {
    delay(100);
    return;
  }

  sensor.read();
  uint16_t distance = sensor.ranging_data.range_mm;
  unsigned long now = millis();
  bool valid = (sensor.ranging_data.range_status == VL53L1X::RangeValid);

  if (valid) {
    sendProfileData(now, distance);
  }

  bool isNear = (distance < SEUIL_MM) && valid;

  if (wasNear && !isNear && (now - lastRepTime > DEBOUNCE_MS)) {
    repCount++;
    totalCount++;
    lastRepTime = now;
    sendCountData();
    Serial.printf("[REP] #%d (total: %d)\n", repCount, totalCount);
  }

  wasNear = isNear;

  static unsigned long lastLog = 0;
  if (now - lastLog > 500) {
    Serial.printf("[SENSOR] %d mm | valid=%d | reps=%d | conn=%d\n",
      distance, valid, repCount, pServer->getConnectedCount());
    lastLog = now;
  }
}
