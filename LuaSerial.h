#ifndef __LUASERIAL__
#define __LUASERIAL__

#include <Arduino.h>
#include "LuaValue.h"
#include "LuaTable.h"
#include "LuaNil.h"
#include "LuaBool.h"
#include "LuaString.h"
#include "LuaNumber.h"

class LuaSerial {
  public:
    static char* SerializeValue(LuaValue* LV) {
      LV->Serialize();
      return LV->GetSerialized();
    }
};

#endif
