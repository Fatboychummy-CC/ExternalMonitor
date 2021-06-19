#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "ComputerCraftTerm.h"
#include "Debug.h"
#include "Commander.h"
#include "LED.h"
#include "Stater.h"

SSD1306AsciiWire window;
ComputerCraftTerm* CCT;
LED* led;
Stater* State;

bool debugMode = true;

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
  Debug::EnableDebugging();
  Debug::SetDebugDelay(200);

  State = new Stater();
  if (debugMode) {
    State->SetState(Stater::State::DEBUGGING);
  } else {
    State->SetState(Stater::State::DISCONNECTED);
  }

  Serial.println(F("Ready."));
  led->magenta();
}

//------------------------------------------------------------------------------
void loop() {
  Stater::State state = State->GetState();
  bool updated = State->IsUpdated();

  if (state == Stater::State::DEBUGGING) {
    if (updated)
      Debug::println("Debug mode enabled.");
    led->blue();
    Commander::RunTerminal(&Serial, CCT);
  } else if (state == Stater::State::CONNECTED) {
    if (updated)
      Debug::println("Connected to network device.");
    led->green();
  } else if (state == Stater::State::DISCONNECTED) { // not debugmode, not connected.
    if (updated)
      Debug::println("Disconnected from network device.");
    led->red();
    Commander::RunBlink(&Serial, CCT);
  } else { // Unknown state.
    if (updated) {
      Debug::print("Unknown state: ");
      Debug::println(state, false);
    }
  }
}
// command format: <op>;<numArgs>;<LType>;<argdata>;
