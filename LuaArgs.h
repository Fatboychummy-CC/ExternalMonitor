#ifndef __LUATABLE__
#define __LUATABLE__

#include <Arduino.h>
#include "LuaValue.h"
#include "Constants.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"

class LuaArgs{
  public:
    LuaArgs();
    ~LuaArgs(); // DOES NOT DESTRUCT INTERNAL OBJECTS!
    void InsertValue(LuaValue* LV);

    LuaValue* At(byte index);

    byte size();
  private:
    static constexpr byte _maxSize = 3;
    LuaValue* Storage[_maxSize];
    byte _size = 0;
};

#endif
