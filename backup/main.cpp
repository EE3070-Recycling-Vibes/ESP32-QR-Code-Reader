#include <Arduino.h>
// #include <esp_camera.h>
#include <ESP32QRCodeReader.h>
#include "WiFiConnection.h"
#include "QRCodeReaderTask.h"
#include "Config.h"
#include "LoadCell.h"

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);
// #define CAMERA_MODEL_AI_THINKER

void setup() {
    Serial.begin(115200);
    Serial.println();

    Serial.println("Starting setup...");

    // Connect to Wi-Fi
    connectToWiFi();

    // Initialize Load Cell
    initializeLoadCell();

    // Setup QRCode reader
    reader.setup();
    reader.beginOnCore(1);
    startQRCodeReaderTask(reader);
}

void loop() {
    delay(1000);
}
