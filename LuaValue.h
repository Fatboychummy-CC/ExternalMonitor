#ifndef __LUAVALUE__
#define __LUAVALUE__

#include "Vector.h"

enum LType {
  uninitialized = 0, string = 1, number = 2, _boolean = 3, table = 4, nil = 5
};

class LuaValue {
  public:
    LuaValue(LType type) : _type(type) {}
    virtual String Serialize() {}
    virtual ~LuaValue() {}

    LType type() {
      return _type;
    }

  private:
    LType _type;
};

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

    String Serialize() {
      String s = F("{");
      for (int i = 0; i < _size; i++) {
        s += Storage[i]->Serialize();
        if (i != _size - 1) s += ",";
      }

      return s + F("}");
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
    int _size = 0;
};

class LuaString: public LuaValue {
  public:
    explicit LuaString(String value) : LuaValue(LType::string) {
      Value = value;
    }
    String Serialize() {
      return String("\"") + Value + String("\"");
    }
    
    String Value = "";
};

class LuaNumber: public LuaValue {
  public:
    LuaNumber(double value) : LuaValue(LType::number) {
      Value = value;
    }

    LuaNumber(String& value) : LuaValue(LType::number) {
      Value = value.toDouble();
    }
  
    String Serialize() {
      return String(Value);
    }
    
    double Value = 0;
};

class LuaNil: public LuaValue {
  public:
    explicit LuaNil() : LuaValue(LType::nil) {};
    String Serialize() {
      return "nil";
    }
};

class LuaBool: public LuaValue {
  public:
    explicit LuaBool(bool value) : LuaValue(LType::_boolean) {
      Value = value;
    }
    explicit LuaBool(String& value) : LuaValue(LType::_boolean) {
      if (value == F("false"))
        Value = false;
      else
        Value = true;
    }
  
    String Serialize() {
      if (Value) return F("true");
      return F("false");
    }
    static bool CollectBool(String& data, String& output, LuaValue* value) {
      String t = data.substring(0, 4), f = data.substring(0, 5);
      if (t == F("true") || f == F("false")) {
        output = (t == F("true")) ? t : f;
        value = new LuaBool((t == F("true")) ? t : f);
        return true;
      }
      return false;
    }
  
    bool Value = false;
};

class LuaSerial {
  public:
    static String SerializeValue(LuaValue* LV) {
      return LV->Serialize();
    }
};

#endif
