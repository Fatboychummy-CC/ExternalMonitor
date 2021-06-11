#ifndef __LUANUMBER__
#define __LUANUMBER__

#include <Arduino.h>
#include "LuaValue.h"
#include "Constants.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"

// any values > 999 will fail to serialize.
class LuaNumber: public LuaValue {
  public:
    LuaNumber(double value);

    LuaNumber(String& value);

    byte Serialize();

    char* GetSerialized();

    double Value = 0;
    static char Serialized[LuaValue::MAX_ALLOC];
};

#endif
