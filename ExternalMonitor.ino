#include <Wire.h>
#include <SoftwareSerial.h>
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
LED* led;
bool connected = true;

//------------------------------------------------------------------------------
void setup() {
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(115200);

  led = new LED(10, 9, 6);
  led->red();

  bool temp = false;
  while (!Serial) {
    temp = !temp;
    if (temp)
      led->red();
    else
      led->white();

    delay(100);
  }
  led->yellow();

  Serial.setTimeout(100);

  CCT = new ComputerCraftTerm(&window);
  D = new Debug(&Serial);
  D->EnableDebugging();
  D->SetDebugDelay(0);

  CCT->useDebugger(D);

  Serial.println(F("Ready."));
  led->magenta();
}

//------------------------------------------------------------------------------
void loop() {
  if (!connected) {
    led->red();
    Commander::RunBlink(&Serial, D, CCT);
  } else {
    led->blue();
    Commander::RunTerminal(&Serial, D, CCT);
  }
}
// command format: <op>;<numArgs>;<LType>;<argdata>;
