#ifndef AIRTABLE_API_H
#define AIRTABLE_API_H

#include <Arduino.h>

void updateAirtableRecord(const String& key, const String& attribute_to_update, const String& new_value);

#endif
