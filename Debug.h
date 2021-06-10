#ifndef __DEBUG__
#define __DEBUG__

#include <Arduino.h>

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
    void SetScope(const char* scope) {
      scoped = true;
      this->scope = scope;
    }
    String GetScope() {
      return this->scope;
    }
    void ClearScope() {
      scoped = false;
    }

    void printScope() {
      if (scoped) {
        s->print(OPEN_BRACKET);
        s->print(scope);
        s->print(CLOSE_BRACKET);
        s->print(SEMICOLON);
        s->print(SPACE);
      }
    }

    void print(const char* data, bool showScope) {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->print(data);
        delay(delayTime);
      }
    }
    void println(const char* data, bool showScope) {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->println(data);
        delay(delayTime);
      }
    }
    void print(const int& data, bool showScope) {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->print(data);
        delay(delayTime);
      }
    }
    void println(const int& data, bool showScope) {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->println(data);
        delay(delayTime);
      }
    }

    void println(const char* data) const {
      this->println(data, true);
    }
    void println(const int& data) const {
      this->println(data, true);
    }
    void print(const char* data) const {
      this->print(data, true);
    }
    void print(const int& data) const {
      this->print(data, true);
    }

  private:
    HardwareSerial* s;
    bool debugEnabled = false, scoped = false;
    short delayTime = 1000;
    char[30] scope;
};

#endif
