#include <Arduino.h>
#include "LuaValue.h"
#include "LuaError.h"
#include "GlobalFunctions.h"
#include "Constants.h"

static char LuaError::Serialized[LuaValue::MAX_ALLOC];

LuaError::LuaError(const char* error) : LuaValue(LType::table) {
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
LuaError::~LuaError() {}

byte LuaError::Serialize() {
  return 7 + valueSize;
}

char* LuaError::GetSerialized() {
  return Serialized;
}
