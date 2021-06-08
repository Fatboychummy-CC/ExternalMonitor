#ifndef __COMPUTERCRAFTTERM__
#define __COMPUTERCRAFTTERM__

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "LuaValue.h"
#include "Debug.h"

/*
 * enum LType {
    uninitialized = 0, string = 1, number = 2, _boolean = 3, table = 4, nil = 5
  };
 * 
 */
enum TermCommands {
  _null = 0,
  getSize = 1, getCursorPos = 2, getCursorBlink = 3, getTextColor = 4, getBackgroundColor = 5, isColor = 6, getPaletteColor = 7, getTextScale = 8,
  write = 9, scroll = 10, clear = 11, clearLine = 12, blit = 13,
  setCursorPos = 14, setCursorBlink = 15, setTextColor = 16, setBackgroundColor = 17, setPaletteColor = 18, setTextScale = 19
};
// command format: <op>;<numArgs>;[<LType>;<argdata>;]
class ComputerCraftTerm {
  public:
    explicit ComputerCraftTerm(SSD1306AsciiWire* screen);

    // Getters
    LuaValue* getSize();
    LuaValue* getCursorPos();
    LuaValue* getCursorBlink();
    LuaValue* getTextColor();
    LuaValue* getBackgroundColor();
    LuaValue* isColor();
    LuaValue* getPaletteColor(int color);
    LuaValue* getTextScale();

    // Writers
    LuaValue* write(String& text);
    LuaValue* scroll(int y);
    LuaValue* clear();
    LuaValue* clearLine();
    LuaValue* blit(String& text, String& textColor, String& backgroundColor);

    // Setters
    LuaValue* setCursorPos(int x, int y);
    LuaValue* setCursorBlink(bool blink);
    LuaValue* setTextColor(int color);
    LuaValue* setBackgroundColor(int color);
    LuaValue* setPaletteColor(int index, int color);
    LuaValue* setPaletteColor(int index, int r, int g, int b);
    LuaValue* setTextScale(double scale);

    LuaValue* RunCommand(int command, LuaTable* arguments);

    // Helpers
    bool argCount(LuaTable* arguments, byte numArgs);
    bool expect(LuaValue* argument, const LType& expected);
    LuaTable* badArg();
    LuaTable* badCommand();

    void useDebugger(Debug* debug);
    
  private:
    SSD1306AsciiWire* oled;
    int cursorX = 0, cursorY = 0, externalX = 1, externalY = 1;
    int textColor = 0, backgroundColor = 0;
    bool cursorBlink = false, hasColor = false;
    Vector<String> charbuffer, textColorBuffer, backgroundColorBuffer;
    Debug* d;
};

#endif
