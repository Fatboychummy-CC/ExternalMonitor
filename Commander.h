#ifndef __COMMANDER__
#define __COMMANDER__

class Commander {
  public:
    static void RunTerminal(const HardwareSerial& S, Debug* d, ComputerCraftTerm* CCT);

    static void RunOnline(const HardwareSerial& S, Debug* d, ComputerCraftTerm* CCT);

    static void RunBlink(const HardwareSerial& S, Debug* d, ComputerCraftTerm* CCT);
};

#endif
