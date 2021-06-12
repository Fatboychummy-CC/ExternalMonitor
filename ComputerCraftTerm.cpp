#include <Wire.h>
#include <Arduino.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "ComputerCraftTerm.h"
#include "LuaValue.h"
#include "LuaTable.h"
#include "LuaNil.h"
#include "LuaBool.h"
#include "LuaString.h"
#include "LuaNumber.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

ComputerCraftTerm::ComputerCraftTerm(SSD1306AsciiWire* screen) {
  oled = screen;
  Wire.begin();
  Wire.setClock(400000L);
#if RST_PIN >= 0
  oled->begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled->begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0

  oled->setFont(System5x7);
  oled->clear();
}


    // getters
LuaValue* ComputerCraftTerm::getSize() {
  LuaTable* LV = new LuaTable();

  LV->InsertValue(new LuaNumber(21));
  LV->InsertValue(new LuaNumber(8));

  return LV;
}

LuaValue* ComputerCraftTerm::getCursorPos() {
  LuaTable* VA = new LuaTable();
  VA->InsertValue(new LuaNumber(externalX));
  VA->InsertValue(new LuaNumber(externalY));

  return VA;
}

LuaValue* ComputerCraftTerm::getCursorBlink() {
  return new LuaBool(cursorBlink);
}

LuaValue* ComputerCraftTerm::getTextColor() {
  return new LuaNumber(textColor);
}

LuaValue* ComputerCraftTerm::getBackgroundColor() {
  return new LuaNumber(backgroundColor);
}

LuaValue* ComputerCraftTerm::isColor() {
  return new LuaBool(hasColor);
}

LuaValue* ComputerCraftTerm::getPaletteColor(int color) {
  return new LuaNumber(0);
}

LuaValue* ComputerCraftTerm::getTextScale() {
  return new LuaNumber(1);
}

    // writers

LuaValue* ComputerCraftTerm::write(char* text) {
  oled->setCursor(cursorX, cursorY); // Ensure cursor is at correct position
  oled->print(text);
  externalX += strlen(text);
  cursorX += (strlen(text) + 1) * oled->fontWidth();

  return new LuaNil();
}

LuaValue* ComputerCraftTerm::write(const char* text) {
  oled->setCursor(cursorX, cursorY);
  oled->print(text);
  externalX += strlen(text);
  cursorX += (strlen(text) + 1) * oled->fontWidth();

  return new LuaNil();
}

LuaValue* ComputerCraftTerm::write(const char& text) {
  oled->setCursor(cursorX, cursorY);
  oled->print(text);
  externalX += 1;
  cursorX += (1 + 1) * oled->fontWidth();

  return new LuaNil();
}

LuaValue* ComputerCraftTerm::scroll(byte y) {
  oled->scrollMemory(y * 8); // characters are a strip of 8 pixels tall

  return new LuaNil();
}

LuaValue* ComputerCraftTerm::clear() {
  oled->clear();

  oled->setCursor(cursorX, cursorY);

  return new LuaNil();
}

LuaValue* ComputerCraftTerm::clearLine() {
  oled->setCursor(0, cursorY);
  oled->clearToEOL();
  oled->setCursor(cursorX, cursorY);

  return new LuaNil();
}

LuaValue* ComputerCraftTerm::blit(char* text, char* textColor, char* backgroundColor) {
  // Ignore textcolor and bgcolor currently, as we are running on a black and white screen which cannot invert colors anyways.

  return this->write(text);
}

    // setters

LuaValue* ComputerCraftTerm::setCursorPos(byte x, byte y) {
  cursorX = (x - 1) * (byte)oled->fontWidth() + (x - 1); // subtract 1 since we index from 0 unlike Lua.
  externalX = x;
  cursorY = (y - 1); // y height is always multiplied by 8 internally.
  externalY = y;

  oled->setCursor(cursorX, cursorY);

  return new LuaNil();
}

LuaValue* ComputerCraftTerm::setCursorBlink(bool blink) {} // I'm unsure how I'll implement cursor blink, will figure that out later.

LuaValue* ComputerCraftTerm::setTextColor(int color) {

}

LuaValue* ComputerCraftTerm::setBackgroundColor(int color) {}

LuaValue* ComputerCraftTerm::setPaletteColor(int index, int color) {}

LuaValue* ComputerCraftTerm::setPaletteColor(int index, int r, int g, int b) {}

    // Scale value between 1 and 10.
    // Input scale multiplied by 2.

LuaValue* ComputerCraftTerm::setTextScale(byte scale) {
  if (scale == 1) {
    oled->set1X();
  } else {
    oled->set2X();
  }
}

void ComputerCraftTerm::useDebugger(Debug* debug) {
  d = debug;
}

bool ComputerCraftTerm::argCount(LuaTable* arguments, byte numArgs) {
  return arguments->size() < numArgs;
}

bool ComputerCraftTerm::expect(LuaValue* argument, const LType& expected) {
  return argument->type() != expected;
}

const char BAD_ARG[]         = "BadArg";
const char BAD_ARGUMENTS[]   = "Bad arguments.";
const char UNKNOWN_COMMAND[] = "Unknown command.";

LuaTable* ComputerCraftTerm::badArg() {
  d->println(BAD_ARG);
  LuaTable* LT = new LuaTable();
  LT->InsertValue(new LuaNil());
  LT->InsertValue(new LuaString(BAD_ARGUMENTS));

  return LT;
}

LuaTable* ComputerCraftTerm::badCommand() {
  d->println(BAD_ARG);
  LuaTable* LT = new LuaTable();
  LT->InsertValue(new LuaNil());
  LT->InsertValue(new LuaString(UNKNOWN_COMMAND));

  return LT;
}

LuaValue* ComputerCraftTerm::RunCommand(byte command, LuaTable* arguments) {
  d->print("Command given: ");
  d->println(command, false);
  switch (command) {
    // getters
    case TermCommands::_null:
      d->println(F("Null"));

      return new LuaNil();
    case TermCommands::getSize:
      d->println(F("getSize"));

      return this->getSize();
    case TermCommands::getCursorPos:
      d->println(F("getCursorPos"));

      return this->getCursorPos();
    case TermCommands::getCursorBlink:
      d->println(F("getCursorBlink"));

      return this->getCursorBlink();
    case TermCommands::getTextColor:
      d->println(F("getTextColor"));

      return this->getTextColor();
    case TermCommands::getBackgroundColor:
      d->println(F("getBackgroundColor"));

      return this->getBackgroundColor();
    case TermCommands::isColor:
      d->println(F("isColor"));

      return this->isColor();
    case TermCommands::getPaletteColor: {
      d->println(F("getPaletteColor"));

      if (argCount(arguments, 1) || expect(arguments->At(0), LType::number))
        return badArg();

      LuaNumber* a1 = arguments->At(0);
      return this->getPaletteColor(a1->Value);
    } case TermCommands::getTextScale: {
      d->println(F("getTextScale"));

      return this->getTextScale();
    } case TermCommands::write: { // writers
      d->println(F("write"));

      if (argCount(arguments, 1) || expect(arguments->At(0), LType::string))
        return badArg();

      LuaString* a1 = arguments->At(0);

      return this->write(a1->Value);
    } case TermCommands::scroll: {
      d->println(F("scroll"));

      if (argCount(arguments, 1) || expect(arguments->At(0), LType::number))
        return badArg();

      LuaNumber* a1 = arguments->At(0);


      return this->scroll(a1->Value);
    } case TermCommands::clear: {
      d->println(F("clear"));

      return this->clear();
    } case TermCommands::clearLine: {
      d->println(F("clearLine"));

      oled->setCursor(0, cursorY);
      oled->clearToEOL();
      oled->setCursor(cursorX, cursorY);

      return new LuaNil();
    } case TermCommands::blit: {
      d->println(F("blit"));

      if (argCount(arguments, 3) || expect(arguments->At(0), LType::string) || expect(arguments->At(1), LType::string) || expect(arguments->At(2), LType::string))
        return badArg();

      LuaString* a1 = arguments->At(0);
      LuaString* a2 = arguments->At(1);
      LuaString* a3 = arguments->At(2);

      // completely ignore coloring because this is black and white and we unfortunately cannot even change the color anyways


      return this->blit(a1->Value, a2->Value, a3->Value);
    } case TermCommands::setCursorPos: { // setters
      d->println(F("setCursorPos"));

      if (argCount(arguments, 2) || expect(arguments->At(0), LType::number) || expect(arguments->At(1), LType::number))
        return badArg();

      LuaNumber* a1 = arguments->At(0);
      LuaNumber* a2 = arguments->At(1);

      return this->setCursorPos(a1->Value, a2->Value);
    } case TermCommands::setCursorBlink: {
      d->println(F("setCursorBlink"));

      if (argCount(arguments, 1) || expect(arguments->At(0), LType::_boolean))
        return badArg();

      LuaBool* a1 = arguments->At(0);

      return this->setCursorBlink(a1);
    } case TermCommands::setTextColor: {
      d->println(F("setTextColor"));

      if (argCount(arguments, 1) || expect(arguments->At(0), LType::number))
        return badArg();

      LuaNumber* a1 = arguments->At(0);

      return this->setTextColor(a1->Value);
    } case TermCommands::setBackgroundColor: {
      d->println(F("setBackgroundColor"));

      if (argCount(arguments, 1) || expect(arguments->At(0), LType::number))
        return badArg();

      LuaNumber* a1 = arguments->At(0);

      return this->setBackgroundColor(a1);
    } case TermCommands::setPaletteColor: {
      d->println(F("setPaletteColor"));
      return new LuaNil();
    } case TermCommands::setTextScale: {
      d->println(F("setTextScale"));
      return new LuaNil();
    } default: {
      d->println(F("default"));

      return badCommand();
    }
  }


  d->println(F("This should never happen."));
  return new LuaString(F("This should never happen."));
}
