#include "Commander.h"
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "ComputerCraftTerm.h"
#include "LuaValue.h"
#include "Debug.h"
#include "LED.h"

String ReadNext(HardwareSerial&);

void Commander::RunTerminal(const HardwareSerial& S, Debug* d, ComputerCraftTerm* CCT) {
  if (S.available()) {
    d->SetScope(F("Loop"));
    String str;
    int op = 0, numArgs = 0;
    LuaTable arguments;
    
    digitalWrite(13, true);

    // read the operation
    str = ReadNext(S);
    
    d->print(F("OP     : "));
    d->println(str, false);
    
    op = str.toInt();

    // read the amount of arguments
    str = ReadNext(S);
    
    d->print(F("NUMARGS: "));
    d->println(str, false);
    
    numArgs = str.toInt();
    
    d->SetScope("ArgLoop");
    // for each argument:
    for (int i = 0; i < numArgs; i++) {
      d->print(F("ARG    : "));
      d->println(i, false);
      int ctype;

      // read the type
      str = ReadNext(S);
      
      d->print(F("  CTYPE  : "));
      d->println(str, false);
      
      ctype = str.toInt();
      

      // read the data for the type
      str = ReadNext(S);
      while (str[str.length() - 1] == '\\') { // catch strings backslash-escaping `;`
        str.remove(str.length() - 1); 
        str += ReadNext(S);
      }

      switch (ctype) {
        case LType::number: {
          arguments.InsertValue(new LuaNumber(str));
          break;
        } case LType::string: {
          arguments.InsertValue(new LuaString(str));
          break;
        } case LType::_boolean: {
          arguments.InsertValue(new LuaBool(str));
          break;
        } default: {
          arguments.InsertValue(new LuaNil());
          break;
        }
      }
      
      d->print(F("  DATA   : "));
      d->println(str, false);
    }
    
    d->SetScope(F("RunCommand"));
    LuaValue* returned = CCT->RunCommand(op, &arguments);
    d->SetScope(F("Loop"));
    
    Serial.print(F("OUTPUT : "));
    Serial.println(LuaSerial::SerializeValue(returned));
    
    delete returned;
  }
  digitalWrite(13, false);
}

void Commander::RunOnline(const HardwareSerial& S, Debug* d, ComputerCraftTerm* CCT) {
  Serial.println(F("This function is not yet available."));
}

void Commander::RunBlink(const HardwareSerial& S, Debug* d, ComputerCraftTerm* CCT) {
  
}

String ReadNext(HardwareSerial& S) {
  return S.readStringUntil(';');
}
