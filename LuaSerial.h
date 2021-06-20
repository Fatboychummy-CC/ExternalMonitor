#ifndef __LUASERIAL__
#define __LUASERIAL__

#include <Arduino.h>
#include "LuaValue.h"

class LuaSerial {
  public:
    static char* SerializeValue(LuaValue* LV) {
      LV->Serialize();
      return LV->GetSerialized();
    }
};

#endif
