#ifndef __LUATWONUM__
#define __LUATWONUM__

#include <Arduino.h>
#include "LuaValue.h"
#include "Constants.h"
#include "GlobalFunctions.h"

class LuaTwoNum : public LuaValue {
  public:
    LuaTwoNum(double value1, double value2);
    LuaTwoNum(String& value1, String& value2);

    byte Serialize();

    char* GetSerialized();

    double Value1 = 0;
    double Value2 = 0;
    static char Serialized[LuaValue::MAX_ALLOC];
};

#endif
