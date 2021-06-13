#include <Arduino.h>
#include "LuaValue.h"
#include "LuaTable.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"

char LuaTable::Serialized[] = "";

LuaTable::LuaTable() : LuaValue(LType::table) {
  for (byte i = 0; i < 5; i++) {
    Storage[i] = nullptr;
  }
}

LuaTable::~LuaTable() {
  for (byte i = 0; i < _size; i++) {
    delete Storage[i];
  }
}

char* LuaTable::GetSerialized() {
  return Serialized;
}

byte LuaTable::size() {
  return _size;
}

byte LuaTable::Serialize() {
  Serial.println("Serialize: Zero");
  delay(400);
  // Clear the buffer.
  Zero(Serialized);

  Serial.println("Serialize: Insert {");
  delay(400);
  // Insert the initial opening brace "{"
  InsertBuffer(Serialized, OPEN_BRACE, 0, LuaValue::MAX_ALLOC);

  // Insert each item in the storage.
  byte insertPos = 1;
  for (byte i = 0; i < _size; i++) {
    Serial.print("Serialize: loop: ");
    Serial.println(i);
    delay(400);

    Serial.println("Serialize: loop: Serialize");
    delay(400);
    // Tell the object to serialize what it is holding.
    if (Storage[i] == nullptr) {
      Serial.println("Serialize: loop: WARNING: current index is nullptr!");
      delay(400);
    }
    Serial.print("Serialize: loop: LuaValue type: ");
    Serial.println(Storage[i]->type());
    delay(400);
    byte len = Storage[i]->Serialize();

    Serial.println("Serialize: loop: check for buffer length issues");
    delay(400);
    // We need to either add a comma or closing brace after this, *and* a null terminator.
    // If we don't have enough space for both, fail.
    if (insertPos + len >= LuaValue::MAX_ALLOC - 3) {
      InsertBuffer(Serialized, SERIALIZE_FAIL, 0, SERIALIZE_FAIL_LEN, LuaValue::MAX_ALLOC);
      return SERIALIZE_FAIL_LEN;
    }

    Serial.println("Serialize: loop: insert current serialized value");
    delay(400);
    // Insert current value "{32"
    InsertBuffer(Serialized, Storage[i]->GetSerialized(), insertPos, len, LuaValue::MAX_ALLOC);

    Serial.println("Serialize: loop: increment position");
    delay(400);
    // increment insertion position by length of string.
    insertPos += len;

    Serial.println("Serialize: loop: insert ,");
    delay(400);
    // Insert comma if we are not at the end. "{32,"
    if (i != _size - 1) {
      InsertBuffer(Serialized, COMMA, insertPos, LuaValue::MAX_ALLOC);
      insertPos++;
    }
  }

  Serial.println("Serialize: insert }");
  delay(400);
  // Insert the closing brace when we're done. "{32,64}"
  InsertBuffer(Serialized, CLOSE_BRACE, insertPos, LuaValue::MAX_ALLOC);

  Serial.println("Serialize: return");
  delay(400);

  return insertPos++; // insertPos + 1 should be the length of the string.
}

void LuaTable::InsertValue(LuaValue* LV) {
  if (_size < 5) {
    Storage[_size++] = LV;
    return;
  }
}

LuaValue* LuaTable::At(byte index) {
  return Storage[index];
}
