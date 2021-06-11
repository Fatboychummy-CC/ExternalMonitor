#include <Arduino.h>
#include "LuaValue.h"
#include "LuaTable.h"

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
  // Clear the buffer.
  LuaValue::Zero(Serialized);

  // Insert the initial opening brace "{"
  InsertBuffer(Serialized, OPEN_BRACE, 0, 1, LuaValue::MAX_ALLOC);

  // Insert each item in the storage.
  byte insertPos = 1;
  for (byte i = 0; i < _size; i++) {
    // Tell the object to serialize what it is holding.
    byte len = Storage[i]->Serialize();

    // We need to either add a comma or closing brace after this, *and* a null terminator.
    // If we don't have enough space for both, fail.
    if (insertPos + len >= LuaValue::MAX_ALLOC - 3) {
      InsertBuffer(Serialized, SERIALIZE_FAIL, 0, SERIALIZE_FAIL_LEN, LuaValue::MAX_ALLOC);
      return SERIALIZE_FAIL_LEN;
    }

    // Insert current value "{32"
    InsertBuffer(Serialized, Storage[i]->GetSerialized(), insertPos, len, LuaValue::MAX_ALLOC);

    // increment insertion position by length of string.
    insertPos += len;

    // Insert comma if we are not at the end. "{32,"
    if (i != _size - 1) {
      InsertBuffer(Serialized, COMMA, insertPos, 1, LuaValue::MAX_ALLOC);
      insertPos++;
    }
  }

  // Insert the closing brace when we're done. "{32,64}"
  InsertBuffer(Serialized, CLOSE_BRACE, insertPos, 1, LuaValue::MAX_ALLOC);

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
