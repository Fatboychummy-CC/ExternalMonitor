#include <Arduino.h>
#include "LuaNumber.h"
#include "LuaValue.h"
#include "Constants.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"

char LuaNumber::Serialized[LuaValue::MAX_ALLOC] = "";

LuaNumber::LuaNumber(double value) : LuaValue(LType::number) {
  Value = value;
}

LuaNumber::LuaNumber(String& value) : LuaValue(LType::number) {
  Value = value.toDouble();
}

byte LuaNumber::Serialize() {
  // Clear the buffer.
  Zero(Serialized);

  // eeeeeeggghhhh
  String str = String(Value); // hopefully using this to convert numbers won't cause memory death?

  // Insert the value.
  InsertBuffer(Serialized, str.c_str(), 0, str.length(), LuaValue::MAX_ALLOC);

  return str.length();
}

char* LuaNumber::GetSerialized() {
  return Serialized;
}
