#ifndef __LUAVALUE__
#define __LUAVALUE__

#include "Vector.h"

enum LType {
  uninitialized = 0, string = 1, number = 2, _boolean = 3, table = 4, nil = 5
};

void InsertBuffer(char* buffer, const char* insert, byte pos, byte insertionSize, byte bufferSize) {
  // protect against out-of-bounds
  //   if the end of our string is going to be "further" than the end of the buffer,
  //   set the length of our string to be the end of the buffer, subtract by the position we're inserting at, subtract 1 for the null.
  if (pos + insertionSize > bufferSize) insertionSize = bufferSize - pos - 1;

  // copy stuff from the insertion to the buffer
  for (byte i = pos; i < pos + insertionSize - 1; i++) {
    buffer[i] = insert[i - pos];
  }

  // Put null character at the end of the inserted string.
  buffer[insertionSize - 1] = '\0';
}

void Zero(char* buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    buffer[i] = 0;
  }
}

bool bufferEqual(char* b1, char* b2, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    if (b1[i] != b2[i]) return false;
  }
  return true;
}

class LuaValue {
  public:
    LuaValue(LType type) : _type(type) {}
    /**
     * @returns the size of the buffer inserted.
     */
    virtual byte Serialize() {}
    virtual ~LuaValue() {}

    LType type() {
      return _type;
    }

  private:
    LType _type;
    static const byte MAX_ALLOC;
};
byte LuaValue::MAX_ALLOC = 30;


const char OPEN_BRACE = '{';
const char CLOSE_BRACE = '}';
const char COMMA = ',';
const char QUOTE = '"';
const char* SERIALIZE_FAIL = "\"Failed to serialize.\"";
const byte SERIALIZE_FAIL_LEN = 22;
class LuaTable: public LuaValue {
  public:
    LuaTable() : LuaValue(LType::table) {
      for (int i = 0; i < 5; i++) {
        Storage[i] = nullptr;
      }
    }
    ~LuaTable() {
      for (int i = 0; i < _size; i++) {
        delete Storage[i];
      }
    }

    byte Serialize() {
      // Clear the buffer.
      Zero(Serialized);

      // Insert the initial opening brace "{"
      InsertBuffer(Serialized, OPEN_BRACE, 0, 1, LuaValue::MAX_ALLOC);

      // Insert each item in the storage.
      byte insertPos = 1;
      for (int i = 0; i < _size; i++) {
        // Tell the object to serialize what it is holding.
        byte len = Storage[i]->Serialize();

        // We need to either add a comma or closing brace after this, *and* a null terminator.
        // If we don't have enough space for both, fail.
        if (insertPos + len >= LuaValue::MAX_ALLOC - 3) {
          InsertBuffer(Serialized, SERIALIZE_FAIL, 0, SERIALIZE_FAIL_LEN, LuaValue::MAX_ALLOC);
          return SERIALIZE_FAIL_LEN;
        }

        // Insert current value "{32"
        InsertBuffer(Serialized, Storage[i].Value, insertPos, len, LuaValue::MAX_ALLOC);

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

    void InsertValue(LuaValue* LV) {
      if (_size < 5) {
        Storage[_size++] = LV;
        return;
      }
    }

    LuaValue* At(int index) {
      return Storage[index];
    }

    int size() {
      return _size;
    }

  private:
    LuaValue* Storage[5];
    static char[LuaValue::MAX_ALLOC] Serialized;
    int _size = 0;
};

class LuaString: public LuaValue {
  public:
    explicit LuaString(const char* value, byte bufferSize) : LuaValue(LType::string) {
      // Clear the buffer.
      Zero(Value);

      // Insert initial quote.
      InsertBuffer(Value, QUOTE, 0, 1, LuaValue::MAX_ALLOC);

      // Insert the value
      InsertBuffer(Value, value, 1, bufferSize, LuaValue::MAX_ALLOC);

      // insert the final quote.
      InsertBuffer(Value, QUOTE, bufferSize + 1, LuaValue::MAX_ALLOC);

      // set the size
      valueSize = bufferSize + 2; // + 2 for 2 quotes.
    }

    byte Serialize() {
      // copy data from object to serialized partition
      Zero(Serialized);
      InsertBuffer(Serialized, Value, 0, valueSize, LuaValue::MAX_ALLOC);
      return valueSize;
    }

    char[LuaValue::MAX_ALLOC] Value;
    byte valueSize;
    static char[LuaValue::MAX_ALLOC] Serialized;
};
byte LuaString::bufferSize = 0;

// any values > 999 will fail to serialize.
class LuaNumber: public LuaValue {
  public:
    LuaNumber(double value) : LuaValue(LType::number) {
      Value = value;
    }

    LuaNumber(String& value) : LuaValue(LType::number) {
      Value = value.toDouble();
    }

    byte Serialize() {
      // Clear the buffer.
      Zero(Serialized);

      // eeeeeeggghhhh
      String str = String(Value); // hopefully using this to convert numbers won't cause memory death?
      char* ptr = str.c_str();

      // Insert the value.
      InsertBuffer(Serialized, ptr, 0, str.length(), LuaValue::MAX_ALLOC);

      return str.length();
    }

    double Value = 0;
    static char[LuaValue::MAX_ALLOC] Serialized;
};

class LuaNil: public LuaValue {
  public:
    explicit LuaNil() : LuaValue(LType::nil) {};
    byte Serialize() {
      return 3;
    }

    static const char* Serialized = "nil"; // No need to change buffer -- always nil.
};

class LuaBool: public LuaValue {
  public:
    explicit LuaBool(bool value) : LuaValue(LType::_boolean) {
      Value = value;
    }
    explicit LuaBool(const char* value) : LuaValue(LType::_boolean) {
      if (bufferEqual(value, "true", 4))
        Value = true;
      else
        Value = false;
    }

    byte Serialize() {
      // Clear the buffer
      Zero(Serialized);

      if (Value) {
        InsertBuffer(Serialized, "true", 0, 4, 6);

        return 4;
      }

      InsertBuffer(Serialized, "false", 0, 5, 6)
      return 5;
    }

    bool Value = false;
    static char[6] Serialized;
};

#endif
