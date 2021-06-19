#ifndef __DEBUG__
#define __DEBUG__

#include <Arduino.h>
#include "Constants.h"
#include "GlobalFunctions.h"

class Debug {
  public:
    static void EnableDebugging();
    static void SetDebugDelay(int n);
    static void SetScope(char* _scope);
    static char* GetScope();
    static void ClearScope();

    static void printScope();

    template<typename T>
    static void print(const T& data, bool showScope = true) {
      if (debugEnabled) {
        if (showScope)
          printScope();
        Serial.print(data);
        delay(delayTime);
      }
    }

    template<typename T>
    static void println(const T& data, bool showScope = true) {
      if (debugEnabled) {
        if (showScope)
          printScope();
        Serial.println(data);
        delay(delayTime);
      }
    }

    static void printRam(bool showScope = true);

    static void printMemory(bool showScope = true);

  private:
    static bool debugEnabled, scoped;
    static short delayTime;
    static char scope[30];
    static char oldScope[30];
};

#endif
