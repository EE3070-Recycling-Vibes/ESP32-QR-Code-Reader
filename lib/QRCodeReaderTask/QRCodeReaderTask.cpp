#include "QRCodeReaderTask.h"
#include "AirtableAPI.h"
#include "LoadCell.h"

void onQrCodeTask(void *pvParameters) {
    ESP32QRCodeReader *reader = (ESP32QRCodeReader *)pvParameters;
    struct QRCodeData qrCodeData;

    while (true) {
        if (reader->receiveQrCode(&qrCodeData, 100)) {
            Serial.println("Found QRCode");
            if (qrCodeData.valid) {
                Serial.print("Payload: ");
                Serial.println((const char *)qrCodeData.payload);

                String key = String((const char *)qrCodeData.payload);
                String attribute_to_update = "Weight";  // The attribute to edit in Airtable

                // Get the weight value from the load cell
                // float weightValue = getWeight();
                float weightValue = 123.4;
                String new_value = String(weightValue, 2);  // Convert float to String with 2 decimal places

                // Now update the Airtable record
                updateAirtableRecord(key, attribute_to_update, new_value);

            } else {
                Serial.print("Invalid: ");
                Serial.println((const char *)qrCodeData.payload);
            }
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void startQRCodeReaderTask(ESP32QRCodeReader &reader) {
    xTaskCreate(onQrCodeTask, "onQrCode", 8 * 1024, (void *)&reader, 4, NULL);
}