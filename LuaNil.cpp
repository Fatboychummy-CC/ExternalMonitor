#include <Arduino.h>
#include "LuaNil.h"
#include "LuaValue.h"
#include "Debug.h"

char LuaNil::Serialized[LuaValue::MAX_ALLOC] = "nil";

LuaNil::LuaNil() : LuaValue(LType::nil) {
  Debug::printRam();
  Debug::println("#######: LuaNil constructed!");
  Debug::print("#######: ");
  Debug::println(this->type(), false);
};
LuaNil::~LuaNil() {
  Debug::printRam();
  Debug::println("#######: LuaNil destructed!");
}

byte LuaNil::Serialize() {
  return 3;
}

char* LuaNil::GetSerialized() {
  return Serialized;
}
