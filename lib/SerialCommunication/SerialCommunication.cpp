#include "SerialCommunication.h"

String getWeightFromSerial() {
    String weight = "";

    // Assuming Serial1 is connected to the Mega 2560
    if (Serial1.available()) {
        weight = Serial1.readStringUntil('\n');
        weight.trim();
        Serial.print("Received weight: ");
        Serial.println(weight);
    } else {
        Serial.println("No data received from Serial1");
    }
    return weight;
}
