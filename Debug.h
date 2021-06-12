#ifndef __DEBUG__
#define __DEBUG__

#include <Arduino.h>
#include "Constants.h"

class Debug {
  public:
    Debug(HardwareSerial* S) {
      s = S;
    }

    void EnableDebugging() {
      debugEnabled = true;
    }
    void SetDebugDelay(int n) {
      delayTime = n;
    }
    void SetScope(char* scope) {
      scoped = true;
      strcpy(this->scope, scope);
    }
    char* GetScope() {
      return this->scope;
    }
    void ClearScope() {
      scoped = false;
    }

    void printScope() const {
      if (scoped) {
        s->print(OPEN_BRACKET);
        s->print(scope);
        s->print(CLOSE_BRACKET);
        s->print(COLON);
        s->print(SPACE);
      }
    }

    template<typename T>
    void print(T& data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->print(data);
        delay(delayTime);
      }
    }

    template<typename T>
    void println(const T& data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->println(data);
        delay(delayTime);
      }
    }

    template<typename T>
    void print(const T& data) const {
      this->print(data, true);
    }

    template<typename T>
    void println(const T& data) const {
      this->println(data, true);
    }

  private:
    HardwareSerial* s;
    bool debugEnabled = false, scoped = false;
    short delayTime = 1000;
    char scope[30];
};

#endif
