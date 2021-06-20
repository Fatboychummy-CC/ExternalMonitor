#include <Arduino.h>
#include "LuaValue.h"
#include "LuaArgs.h"
#include "GlobalFunctions.h"

LuaArgs::LuaArgs(){
  for (byte i = 0; i < _maxSize; i++) {
    Storage[i] = nullptr;
  }
}

LuaArgs::~LuaArgs() {
  for (byte i = 0; i < _size; i++) {
    delete Storage[i];
  }
}

byte LuaArgs::size() {
  return _size;
}

void LuaArgs::InsertValue(LuaValue* LV) {
  if (_size < _maxSize) {
    Storage[_size++] = LV;
    return;
  }
}

LuaValue* LuaArgs::At(byte index) {
  return Storage[index];
}
