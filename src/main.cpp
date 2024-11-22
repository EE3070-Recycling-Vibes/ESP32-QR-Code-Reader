#include <Arduino.h>
#include <ESP32QRCodeReader.h>

// See available models on README.md or ESP32CameraPins.h
ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

// Function Declarations
void onQrCodeTask(void *pvParameters);

// Serial communication ports
#define RXp2 4
#define TXp2 2

// Read QRCode and send to Airtable
void onQrCodeTask(void *pvParameters)
{
  struct QRCodeData qrCodeData;
  
  Serial.println("Waiting for QRCode");

	// Serial port for communication with the Arduino Uno
	Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);

  while (true)
  {
    Serial.print(".");
    if (reader.receiveQrCode(&qrCodeData, 100))
    {
      Serial.println("\nFound QRCode");
      if (qrCodeData.valid)
      {
        Serial.print("Payload: ");
        Serial.println((const char *)qrCodeData.payload);
        Serial2.println((const char *)qrCodeData.payload);
        Serial2.flush();
        Serial.println("Sent to Arduino Uno");
      }
      else
      {
        Serial.print("Invalid: ");
        Serial.println((const char *)qrCodeData.payload);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("ESP32 QRCode Reader");
  // Setup QRCode reader
  reader.setup();
  reader.beginOnCore(1);
  xTaskCreate(onQrCodeTask, "onQrCode", 4 * 1024, NULL, 4, NULL);
}

void loop()
{
  delay(1000);
}