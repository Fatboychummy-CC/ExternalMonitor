#include "LuaValue.h"
#include "Debug.h"

LuaValue::LuaValue(const LType& type): _type(type) {
 Debug::print("########: LuaValue constructed! Type: ");
 Debug::println(_type, false);
}

LuaValue::~LuaValue() {
  Debug::print("########: LuaValue deconstructed! Type: ");
  Debug::println(_type, false);
}
