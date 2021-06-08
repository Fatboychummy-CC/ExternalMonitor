#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "ComputerCraftTerm.h"
#include "LuaValue.h"
#include "Debug.h"
#include "Commander.h"
#include "LED.h"

SSD1306AsciiWire window;
Debug* D;
ComputerCraftTerm* CCT;
bool connected = false;
//------------------------------------------------------------------------------
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(100);

  CCT = new ComputerCraftTerm(&window);
  D = new Debug(&Serial);
  D->EnableDebugging();
  D->SetDebugDelay(150);

  CCT->useDebugger(D);

  Serial.println(F("Ready."));
}

//------------------------------------------------------------------------------
void loop() {
  if (!connected) 
    Commander::RunBlink(Serial, D, CCT);
  else
    Commander::RunTerminal(Serial, D, CCT);
}
// command format: <op>;<numArgs>;<LType>;<argdata>;
