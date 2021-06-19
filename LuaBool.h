#ifndef __LUABOOL__
#define __LUABOOL__

#include <Arduino.h>
#include "LuaValue.h"
#include "GlobalFunctions.h"

class LuaBool: public LuaValue {
  public:
    explicit LuaBool(bool value);
    explicit LuaBool(char* value);

    byte Serialize();

    char* GetSerialized();

    bool Value = false;
    static char Serialized[6];
};

#endif
