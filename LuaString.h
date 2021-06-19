#ifndef __LUASTRING__
#define __LUASTRING__

#include <Arduino.h>
#include "LuaValue.h"
#include "Constants.h"
#include "GlobalFunctions.h"

class LuaString: public LuaValue {
  public:
    explicit LuaString(const String& value);
    explicit LuaString(char* value);
    explicit LuaString(const char* value);
    ~LuaString();

    byte Serialize();

    char* GetSerialized();

    static char Serialized[LuaValue::MAX_ALLOC];
    char Value[LuaValue::MAX_ALLOC];
    byte valueSize;
};

#endif
