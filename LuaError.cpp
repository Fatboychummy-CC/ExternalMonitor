#include <Arduino.h>
#include "LuaValue.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"

static char Serialized[LuaValue::MAX_ALLOC];

explicit LuaError(const char& error) {
  valueSize = strlen(error);
  Zero(Value);

  Zero(Serialized, LuaValue::MAX_ALLOC);
  // [                 ]

  InsertBuffer(Serialized, OPEN_BRACE, 0, LuaValue::MAX_ALLOC);
  // [{                ]

  InsertBuffer(Serialized, NIL, 1, 3, LuaValue::MAX_ALLOC);
  // [{nil             ]

  InsertBuffer(Serialized, COMMA, 4, LuaValue::MAX_ALLOC);
  // [{nil,            ]

  InsertBuffer(Serialized, QUOTE, 5, LuaValue::MAX_ALLOC);
  // [{nil,"           ]

  InsertBuffer(Serialized, error, 6, valueSize, LuaValue::MAX_ALLOC);
  // [{nil,"Error!     ]

  InsertBuffer(Serialized, QUOTE, 6 + valueSize, LuaValue::MAX_ALLOC);
  // [{nil,"Error!"    ]

  InsertBuffer(Serialized, CLOSE_BRACE, 7 + valueSize, LuaValue::MAX_ALLOC);
  // [{nil,"Error!"}   ]
}
~LuaError() {}


/*
void InsertBuffer(char* buffer, const char* insert, byte pos, byte insertionSize, byte bufferSize)

void InsertBuffer(char* buffer, char* insert, byte pos, byte insertionSize, byte bufferSize)

void InsertBuffer(char* buffer, const char& insert, byte pos, byte bufferSize)
*/

byte Serialize() {
  return 7 + valueSize;
}

char* GetSerialized() {
  return Serialized;
}
