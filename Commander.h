#ifndef __COMMANDER__
#define __COMMANDER__

#include <Arduino.h>
#include <Wire.h>
#include "Debug.h"
#include "ComputerCraftTerm.h"
#include "LED.h"

class Commander {
  public:
    static void RunTerminal(HardwareSerial* S, Debug* d, ComputerCraftTerm* CCT);

    static void RunOnline(HardwareSerial* S, Debug* d, ComputerCraftTerm* CCT);

    static void RunBlink(HardwareSerial* S, Debug* d, ComputerCraftTerm* CCT);

    static bool blinkState;
    static bool blinkSet;
};

#endif
