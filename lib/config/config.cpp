#include "config.h"

// Wi-Fi credentials
const char* ssid = "skyz";
const char* password = "12345678";

// Airtable API details
const String base_id = "appakXV1CGLExzpXQ";       // Replace with your Base ID
const String table_name = "Table 1";    // URL encoded if necessary
const String api_key = "pat4zRxa10XxwbOla.20ae931888e878908b6e094240bd66b16983f3b8c2eb50e36e44f3ab85fb127b";      // Replace with your API Key
const String airtable_url = "https://api.airtable.com/v0/" + base_id + "/" + table_name;