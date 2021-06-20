#include <Arduino.h>
#include "LuaValue.h"
#include "Constants.h"
#include "GlobalFunctions.h"

char LuaTwoNum::Serialized[LuaValue::MAX_ALLOC] = "";

LuaTwoNum::LuaTwoNum(double value1, double value2) : LuaValue(LType::number), Value1(value1), Value2(value2) {}

LuaTwoNum::LuaTwoNum(String& value1, String& value2) : LuaValue(LType::number) {
  Value1 = value1.toDouble();
  Value2 = value2.toDouble();
}


byte LuaTwoNum::Serialize() {
  // Clear the buffer.
  Zero(Serialized);

  // eeeeeeggghhhh
  String str1 = String(Value1); // hopefully using this to convert numbers won't cause memory death?
  byte len1 = str1.length();
  String str2 = String(Value2);
  byte len2 = str2.length();

  InsertBuffer(Serialized, OPEN_BRACE, 0, LuaValue::MAX_ALLOC);
  // '{                 '

  InsertBuffer(Serialized, str1.c_str(), 1, len1, LuaValue::MAX_ALLOC);
  // '{432.374          '

  InsertBuffer(Serialized, COMMA, len1 + 1, LuaValue::MAX_ALLOC);
  // '{432.374,         '

  InsertBuffer(Serialized, str2.c_str(), len1 + 2, len2, LuaValue::MAX_ALLOC);
  // '{432.374,729.674  '

  InsertBuffer(Serialized, CLOSE_BRACE, len1 + len2 + 3, LuaValue::MAX_ALLOC);
  // '{432.374,729.674}'

  return len1 + len2 + 3;
}

char* LuaTwoNum::GetSerialized() {
  return Serialized;
}
