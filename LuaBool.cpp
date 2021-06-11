#include <Arduino.h>
#include "LuaBool.h"
#include "LuaValue.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"

char LuaBool::Serialized[6];

LuaBool::LuaBool(bool value) : LuaValue(LType::_boolean) {
  Value = value;
}
LuaBool::LuaBool(char* value) : LuaValue(LType::_boolean) {
  if (BufferEqual(value, "true", 4))
    Value = true;
  else
    Value = false;
}

byte LuaBool::Serialize() {
  // Clear the buffer
  LuaValue::Zero(Serialized);

  if (Value) {
    InsertBuffer(Serialized, "true", 0, 4, 6);

    return 4;
  }

  InsertBuffer(Serialized, "false", 0, 5, 6);
  return 5;
}

char* LuaBool::GetSerialized() {
  return Serialized;
}
