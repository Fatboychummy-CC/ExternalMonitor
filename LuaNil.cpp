#include <Arduino.h>
#include "LuaNil.h"
#include "LuaValue.h"

char LuaNil::Serialized[4] = "nil";

LuaNil::LuaNil() : LuaValue(LType::nil) {};

byte LuaNil::Serialize() {
  return 3;
}

char* LuaNil::GetSerialized() {
  return Serialized;
}
