#include <Arduino.h>
#include "Commander.h"
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "ComputerCraftTerm.h"
#include "LuaValue.h"
#include "LuaTable.h"
#include "LuaNil.h"
#include "LuaBool.h"
#include "LuaString.h"
#include "LuaNumber.h"
#include "LuaSerial.h"
#include "Debug.h"
#include "LED.h"
#include "Constants.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"

String ReadNext(HardwareSerial*);

bool Commander::blinkState = false;
bool Commander::blinkSet = false;

const char OP[]     = "OP     : ";
const char N_ARGS[] = "NUMARGS: ";
const char ARG[]    = "ARG    : ";
const char CTYPE[]  = "CTYPE  : ";
const char DATA[]   = "DATA   : ";
const char OUT[]    = "OUTPUT : ";

const char LOOP_SCOPE[] = "Loop";
const char ARG_LOOP_SCOPE[] = "ArgLoop";
const char RUN_COMMAND_SCOPE[] = "RunCommand";
const char BLINK_SCOPE[] = "Blink";

void Commander::RunTerminal(HardwareSerial* S, Debug* d, ComputerCraftTerm* CCT) {
  Commander::blinkSet = false;
  if (S->available()) {
    d->SetScope(LOOP_SCOPE);
    String str;
    byte op = 0, numArgs = 0;
    LuaTable arguments;

    digitalWrite(13, true);

    // read the operation
    str = ReadNext(S);

    d->print(OP);
    d->println(str, false);

    op = str.toInt();

    // read the amount of arguments
    str = ReadNext(S);

    d->print(N_ARGS);
    d->println(str, false);

    numArgs = str.toInt();

    d->SetScope(ARG_LOOP_SCOPE);
    // for each argument:
    for (byte i = 0; i < numArgs; i++) {
      d->print(ARG);
      d->println(i, false);
      byte ctype;

      // read the type
      str = ReadNext(S);

      d->print(CTYPE);
      d->println(str, false);

      ctype = str.toInt();


      // read the data for the type
      str = ReadNext(S);
      while (str[str.length() - 1] == BACKSLASH) { // catch strings backslash-escaping `;`
        str.remove(str.length() - 1);
        str += ReadNext(S);
      }

      switch (ctype) {
        case LType::number: {
          arguments.InsertValue(new LuaNumber(str)); // LuaNumber is not converted to c_string.
          break;
        } case LType::string: {
          arguments.InsertValue(new LuaString(str.c_str())); // LuaString isconverted to c_string.
          break;
        } case LType::_boolean: {
          arguments.InsertValue(new LuaBool(str.c_str())); // LuaBool is converted to c_string.
          break;
        } default: {
          arguments.InsertValue(new LuaNil());
          break;
        }
      }

      d->print(DATA);
      d->println(str, false);
    }

    d->SetScope(RUN_COMMAND_SCOPE);
    LuaValue* returned = CCT->RunCommand(op, &arguments);
    d->SetScope(LOOP_SCOPE);

    S->print(OUT);
    S->println(LuaSerial::SerializeValue(returned));

    d->printMemory();

    delete returned;
  }
  digitalWrite(13, false);
}

void Commander::RunOnline(HardwareSerial* S, Debug* d, ComputerCraftTerm* CCT) {
  Commander::blinkSet = false;
  Serial.println(UNAVAILABLE);
}

void Commander::RunBlink(HardwareSerial* S, Debug* d, ComputerCraftTerm* CCT) {
  digitalWrite(13, Commander::blinkState);

  // clear and draw the chevron only once so it doesn't flicker
  if (!Commander::blinkSet) {
    d->SetScope(BLINK_SCOPE);
    d->println(NO_CONNECTION);
    CCT->clear();
    CCT->setTextScale(2);
    CCT->setCursorPos(1, 1);
    CCT->write(CHEVRON);
  }

  // Blink the _
  // if blinkState is true, draw a space, else draw an underscore.
  Commander::blinkSet = true;
  if (Commander::blinkState) {
    Commander::blinkState = false;
    LuaNil* x = CCT->setCursorPos(2, 1);
    LuaNil* y = CCT->write(SPACE);

    delete x;
    delete y;
  } else {
    Commander::blinkState = true;
    LuaNil* x = CCT->setCursorPos(2, 1);
    LuaNil* y = CCT->write(UNDERSCORE);

    delete x;
    delete y;
  }

  // CraftOS cursor-blink delay is 400ms.
  delay(400);
}

String ReadNext(HardwareSerial* S) {
  return S->readStringUntil(SEMICOLON);
}
