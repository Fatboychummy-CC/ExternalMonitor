#ifndef __LUANIL__
#define __LUANIL__

#include <Arduino.h>
#include "LuaValue.h"

class LuaNil: public LuaValue {
  public:
    explicit LuaNil();
    byte Serialize();

    char* GetSerialized();

    static char Serialized[4];
};

#endif
