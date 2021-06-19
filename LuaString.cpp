#include <Arduino.h>
#include "LuaString.h"
#include "LuaValue.h"
#include "Constants.h"
#include "GlobalFunctions.h"

char LuaString::Serialized[LuaValue::MAX_ALLOC] = "";

LuaString::LuaString(const String& value) : LuaValue(LType::string) {
  // Clear the buffer.
  Zero(Value);

  // Insert initial quote.
  InsertBuffer(Value, QUOTE, 0, LuaValue::MAX_ALLOC);

  // Insert the value
  InsertBuffer(Value, value.c_str(), 1, value.length(), LuaValue::MAX_ALLOC);

  // insert the final quote.
  InsertBuffer(Value, QUOTE, value.length() + 1, LuaValue::MAX_ALLOC);

  // set the size
  valueSize = value.length() + 2; // + 2 for 2 quotes.
}

LuaString::LuaString(char* value) : LuaValue(LType::string) {
  byte bufferSize = strlen(value);

  // Clear the buffer.
  Zero(Value);

  // Insert initial quote.
  InsertBuffer(Value, QUOTE, 0, LuaValue::MAX_ALLOC);

  // Insert the value
  InsertBuffer(Value, value, 1, bufferSize, LuaValue::MAX_ALLOC);

  // insert the final quote.
  InsertBuffer(Value, QUOTE, bufferSize + 1, LuaValue::MAX_ALLOC);

  // set the size
  valueSize = bufferSize + 2; // + 2 for 2 quotes.
}

LuaString::LuaString(const char* value) : LuaValue(LType::string) {
  byte bufferSize = strlen(value);

  // Clear the buffer.
  Zero(Value);

  // Insert initial quote.
  InsertBuffer(Value, QUOTE, 0, LuaValue::MAX_ALLOC);

  // Insert the value
  InsertBuffer(Value, value, 1, bufferSize, LuaValue::MAX_ALLOC);

  // insert the final quote.
  InsertBuffer(Value, QUOTE, bufferSize + 1, LuaValue::MAX_ALLOC);

  // set the size
  valueSize = bufferSize + 2; // + 2 for 2 quotes.
}

LuaString::~LuaString() {
  delete Value;
}

byte LuaString::Serialize() {
  // copy data from object to serialized partition
  Zero(Serialized);
  InsertBuffer(Serialized, Value, 0, valueSize, LuaValue::MAX_ALLOC);
  return valueSize;
}

char* LuaString::GetSerialized() {
  return Serialized;
}
