#ifndef __LUANIL__
#define __LUANIL__

#include <Arduino.h>
#include "LuaValue.h"

class LuaNil: public LuaValue {
  public:
    explicit LuaNil();
    ~LuaNil();
    byte Serialize();

    char* GetSerialized();

    static char Serialized[LuaValue::MAX_ALLOC];
};

#endif
