#include "LoadCell.h"
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;  // Data Output Pin
const int LOADCELL_SCK_PIN = 5;   // Serial Clock Pin

HX711 scale;

void initializeLoadCell() {
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

    // Calibration factor; you need to calibrate your scale to get this value
    float calibration_factor = -7050.0;  // Replace with your calibration factor
    scale.set_scale(calibration_factor);
    scale.tare();  // Reset the scale to zero

    Serial.println("Load cell initialized.");
}

float getWeight() {
    if (scale.is_ready()) {
        float weight = scale.get_units(5);  // Average over 5 readings
        Serial.print("Weight: ");
        Serial.println(weight);
        return weight;
    } else {
        Serial.println("HX711 not found.");
        return 0.0;
    }
}
