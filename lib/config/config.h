#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Wi-Fi credentials
extern const char* ssid;
extern const char* password;

// Airtable API details
extern const String base_id;
extern const String table_name;
extern const String api_key;
extern const String airtable_url;

#endif
