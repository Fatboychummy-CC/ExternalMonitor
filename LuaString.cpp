#include <Arduino.h>
#include "LuaString.h"
#include "LuaValue.h"
#include "Constants.h"
#include "GlobalFunctions.h"

char LuaString::Serialized[LuaValue::MAX_ALLOC] = "";

LuaString::LuaString(const String& value) : LuaValue(LType::string) {
  // Clear the buffer.
  Zero(Value);

  // Insert the value
  InsertBuffer(Value, value.c_str(), 0, value.length(), LuaValue::MAX_ALLOC);

  // set the size
  valueSize = value.length(); // + 2 for 2 quotes.
}

LuaString::LuaString(char* value) : LuaValue(LType::string) {
  byte bufferSize = strlen(value);

  // Clear the buffer.
  Zero(Value);

  // Insert the value
  InsertBuffer(Value, value, 0, bufferSize, LuaValue::MAX_ALLOC);

  // set the size
  valueSize = bufferSize; // + 2 for 2 quotes.
}

LuaString::LuaString(const char* value) : LuaValue(LType::string) {
  byte bufferSize = strlen(value);

  // Clear the buffer.
  Zero(Value);

  // Insert the value
  InsertBuffer(Value, value, 0, bufferSize, LuaValue::MAX_ALLOC);

  // set the size
  valueSize = bufferSize; // + 2 for 2 quotes.
}

LuaString::~LuaString() {
  delete Value;
}

byte LuaString::Serialize() {
  // copy data from object to serialized partition
  Zero(Serialized);

  InsertBuffer(Serialized, QUOTE, 0, LuaValue::MAX_ALLOC);

  InsertBuffer(Serialized, Value, 1, valueSize, LuaValue::MAX_ALLOC);

  InsertBuffer(Serialized, QUOTE, valueSize + 1, LuaValue::MAX_ALLOC);

  return valueSize + 2;
}

char* LuaString::GetSerialized() {
  return Serialized;
}
