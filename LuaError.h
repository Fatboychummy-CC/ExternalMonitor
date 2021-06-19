#ifndef __LUAERROR__
#define __LUAERROR__

#include <Arduino.h>
#include "LuaValue.h"

class LuaError: public LuaValue {
  public:
    explicit LuaError(const char& error);
    ~LuaError();

    byte Serialize();
    char* GetSerialized();

    static constexpr byte maxStringSize = LuaValue::MAX_ALLOC - 8;
    char Value[maxStringSize];
    byte valueSize;
    static char Serialized[LuaValue::MAX_ALLOC];
};

#endif // __LUAERROR__
