#include <Arduino.h>
#include "Commander.h"
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "ComputerCraftTerm.h"
#include "LuaValue.h"
#include "LuaArgs.h"
#include "LuaNil.h"
#include "LuaBool.h"
#include "LuaString.h"
#include "LuaNumber.h"
#include "LuaSerial.h"
#include "Debug.h"
#include "LED.h"
#include "Constants.h"
#include "GlobalFunctions.h"

void ReadNext(HardwareSerial*, char* str, byte len);

bool Commander::blinkState = false;
bool Commander::blinkSet = false;
char Commander::_commandData[_COMMAND_DATA_LEN] = "";

void Commander::RunTerminal(HardwareSerial* S, ComputerCraftTerm* CCT) {
  Commander::blinkSet = false;
  if (S->available()) {
    byte op = 0, numArgs = 0;
    LuaArgs arguments;


    Debug::SetScope(LOOP_SCOPE);

    // zero the array, then collect opcode.
    Zero(_commandData, _COMMAND_DATA_LEN);
    ReadNext(S, _commandData, _COMMAND_DATA_LEN);
    Debug::print(OP);
    Debug::println(_commandData, false);
    op = atoi(_commandData);

    // Zero again, collect number args.
    Zero(_commandData, _COMMAND_DATA_LEN);
    ReadNext(S, _commandData, _COMMAND_DATA_LEN);
    Debug::print(N_ARGS);
    Debug::println(_commandData, false);
    numArgs = atoi(_commandData);

    // for each argument:
    for (byte i = 0; i < numArgs; i++) {
/*
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

      Debug::print(DATA);
      Debug::println(str, false);
*/
    }

    Debug::SetScope(RUN_COMMAND_SCOPE);
    LuaValue* returned = CCT->RunCommand(op, &arguments);
    Debug::SetScope(LOOP_SCOPE);
    Debug::print(OUT);
    Debug::println(LuaSerial::SerializeValue(returned), false); // Failing upon all or just things containing LuaStrings?

    Debug::printRam();

    delete returned;
  }
  digitalWrite(13, false);
}

void Commander::RunOnline(HardwareSerial* S, ComputerCraftTerm* CCT) {
  Commander::blinkSet = false;
  Serial.println(UNAVAILABLE);
}

void Commander::RunBlink(HardwareSerial* S, ComputerCraftTerm* CCT) {
  digitalWrite(13, Commander::blinkState);

  // clear and draw the chevron only once so it doesn't flicker
  if (!Commander::blinkSet) {
    Debug::SetScope(BLINK_SCOPE);
    Debug::println(NO_CONNECTION);
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

void ReadNext(HardwareSerial* S, char* str, byte len) {
  S->readBytesUntil(SEMICOLON, str, len - 2);
}
