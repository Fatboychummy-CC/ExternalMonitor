#include <Arduino.h>
#include "LuaNil.h"
#include "LuaValue.h"

char LuaNil::Serialized[LuaValue::MAX_ALLOC] = "nil";

LuaNil::LuaNil() : LuaValue(LType::nil) {};

byte LuaNil::Serialize() {
  Serial.println("Serialize: loop: nil value: return 3");
  delay(400);
  return 3;
}

char* LuaNil::GetSerialized() {
  Serial.println("Serialize: loop: nil value: return serialized value");
  delay(400);
  return Serialized;
}
