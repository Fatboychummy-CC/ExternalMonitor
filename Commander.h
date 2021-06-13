#ifndef __COMMANDER__
#define __COMMANDER__

#include <Arduino.h>
#include <Wire.h>
#include "Debug.h"
#include "ComputerCraftTerm.h"
#include "LED.h"

class Commander {
  public:
    static void RunTerminal(HardwareSerial* S, ComputerCraftTerm* CCT);

    static void RunOnline(HardwareSerial* S, ComputerCraftTerm* CCT);

    static void RunBlink(HardwareSerial* S, ComputerCraftTerm* CCT);

    static bool blinkState;
    static bool blinkSet;

  private:
    static constexpr byte _COMMAND_DATA_LEN = 50;
    static char _commandData[_COMMAND_DATA_LEN];
};

#endif
