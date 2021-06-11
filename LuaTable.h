#ifndef __LUATABLE__
#define __LUATABLE__

#include <Arduino.h>
#include "LuaValue.h"
#include "Constants.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"

class LuaTable: public LuaValue {
  public:
    LuaTable();
    ~LuaTable(); // DOES NOT DESTRUCT INTERNAL OBJECTS!

    byte Serialize();

    void InsertValue(LuaValue* LV);

    LuaValue* At(byte index);

    byte size();

    char* GetSerialized();

    static char Serialized[LuaValue::MAX_ALLOC];
  private:
    LuaValue* Storage[5];
    byte _size = 0;
};

#endif
