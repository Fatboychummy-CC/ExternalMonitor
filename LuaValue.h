#ifndef __LUAVALUE__
#define __LUAVALUE__

#include <Arduino.h>
#include "Constants.h"

enum LType : byte {
  uninitialized = 0, string = 1, number = 2, _boolean = 3, table = 4, nil = 5
};

class LuaValue {
  public:
    LuaValue(LType type) : _type(type) {}
    /**
     * @returns the size of the buffer inserted.
     */
    virtual byte Serialize() = 0;
    virtual ~LuaValue() {}

    virtual char* GetSerialized() = 0;

    LType type() {
      return _type;
    }

    static constexpr byte MAX_ALLOC = 30;
  private:
    LType _type;
};

#endif
