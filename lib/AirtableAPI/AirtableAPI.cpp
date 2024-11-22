#include "AirtableAPI.h"
#include <HTTPClient.h>
#include "Config.h"
#include <ArduinoJson.h>

void updateAirtableRecord(const String& key, const String& attribute_to_update, const String& new_value) {
    // Build the GET request URL with filterByFormula
    String getUrl = airtable_url + "?filterByFormula=" + "{" + "KeyField" + "}='" + key + "'";

    HTTPClient http;
    http.begin(getUrl);
    http.addHeader("Authorization", "Bearer " + api_key);

    int httpCode = http.GET();

    if (httpCode > 0) {
        String payload = http.getString();
        Serial.println("GET response:");
        Serial.println(payload);

        // Parse the JSON response to get the record ID
        DynamicJsonDocument doc(2048);
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.f_str());
            return;
        }

        JsonArray records = doc["records"].as<JsonArray>();

        if (!records || records.size() == 0) {
            Serial.println("No records found.");
            return;
        }

        String recordId = records[0]["id"].as<String>();

        Serial.print("Record ID: ");
        Serial.println(recordId);

        // Now perform PATCH request to update the record
        String patchUrl = airtable_url + "/" + recordId;

        // Prepare JSON payload
        DynamicJsonDocument patchDoc(1024);
        JsonObject fields = patchDoc.createNestedObject("fields");
        fields[attribute_to_update] = new_value;

        String patchPayload;
        serializeJson(patchDoc, patchPayload);

        http.begin(patchUrl);
        http.addHeader("Authorization", "Bearer " + api_key);
        http.addHeader("Content-Type", "application/json");

        int patchHttpCode = http.PATCH(patchPayload);

        if (patchHttpCode > 0) {
            String patchResponse = http.getString();
            Serial.println("PATCH response:");
            Serial.println(patchResponse);
        } else {
            Serial.print("Error on sending PATCH request: ");
            Serial.println(http.errorToString(patchHttpCode));
        }
    } else {
        Serial.print("Error on sending GET request: ");
        Serial.println(http.errorToString(httpCode));
    }

    http.end();
}
