#include <Adafruit_NeoPixel.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define NEOPIXEL_PIN 38
#define NUM_PIXELS 1

// Nordic UART Service (NUS)
#define SERVICE_UUID "6e400001-b5a3-f393-e0a9-e50e24dcca9e"

// Phone -> ESP32
#define RX_CHARACTERISTIC_UUID "6e400002-b5a3-f393-e0a9-e50e24dcca9e"

// ESP32 -> Phone
#define TX_CHARACTERISTIC_UUID "6e400003-b5a3-f393-e0a9-e50e24dcca9e"

Adafruit_NeoPixel pixel(
    NUM_PIXELS,
    NEOPIXEL_PIN,
    NEO_RGB + NEO_KHZ800
);

BLECharacteristic *txCharacteristic = nullptr;


// ----------------------------------------------------
// Called when the phone writes data to the RX
// characteristic.
// ----------------------------------------------------
class CommandCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *characteristic) override {
        String value = characteristic->getValue();

        if (value.length() == 0) {
            return;
        }

        char command = value[0];

        Serial.print("Received: ");
        Serial.println(command);

        if (command == '1') {
            pixel.setPixelColor(
                0,
                pixel.Color(255, 0, 0)
            );

            pixel.show();

            Serial.println("LED: ON");

            if (txCharacteristic != nullptr) {
                txCharacteristic->setValue("LED: ON\n");
                txCharacteristic->notify();
            }
        }

        else if (command == '0') {
            pixel.clear();
            pixel.show();

            Serial.println("LED: OFF");

            if (txCharacteristic != nullptr) {
                txCharacteristic->setValue("LED: OFF\n");
                txCharacteristic->notify();
            }
        }

        else {
            Serial.println("Unknown command");

            if (txCharacteristic != nullptr) {
                txCharacteristic->setValue(
                    "Unknown command. Send 1 or 0.\n"
                );

                txCharacteristic->notify();
            }
        }
    }
};


// ----------------------------------------------------
// BLE connection / disconnection events
// ----------------------------------------------------
class ServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *server) override {
        Serial.println("BLE client connected");
    }

    void onDisconnect(BLEServer *server) override {
        Serial.println("BLE client disconnected");

        BLEDevice::startAdvertising();

        Serial.println("BLE advertising restarted");
    }
};


void setup() {
    Serial.begin(9600);

    delay(1000);

    // ------------------------------------------------
    // NeoPixel initialization
    // ------------------------------------------------
    pixel.begin();
    pixel.clear();
    pixel.show();

    // ------------------------------------------------
    // BLE initialization
    // ------------------------------------------------
    BLEDevice::init("ESP32-S3-COMCS");

    Serial.print("BLE address: ");
    Serial.println(
        BLEDevice::getAddress().toString()
    );

    // ------------------------------------------------
    // BLE Server
    // ------------------------------------------------
    BLEServer *server =
        BLEDevice::createServer();

    server->setCallbacks(
        new ServerCallbacks()
    );

    // ------------------------------------------------
    // Nordic UART Service
    // ------------------------------------------------
    BLEService *service =
        server->createService(
            SERVICE_UUID
        );

    // ------------------------------------------------
    // RX characteristic
    // Phone -> ESP32
    // ------------------------------------------------
    BLECharacteristic *rxCharacteristic =
        service->createCharacteristic(
            RX_CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_WRITE_NR
        );

    rxCharacteristic->setCallbacks(
        new CommandCallbacks()
    );

    // ------------------------------------------------
    // TX characteristic
    // ESP32 -> Phone
    // ------------------------------------------------
    txCharacteristic =
        service->createCharacteristic(
            TX_CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_NOTIFY
        );

    txCharacteristic->addDescriptor(
        new BLE2902()
    );

    // ------------------------------------------------
    // Start BLE service
    // ------------------------------------------------
    service->start();

    // ------------------------------------------------
    // Advertising
    // ------------------------------------------------
    BLEAdvertising *advertising =
        BLEDevice::getAdvertising();

    advertising->addServiceUUID(
        SERVICE_UUID
    );

    advertising->setScanResponse(true);

    BLEDevice::startAdvertising();

    Serial.println(
        "BLE ready - waiting for connection..."
    );
}


void loop() {
    // Nothing required here.
    // BLE communication is handled using callbacks.
}
