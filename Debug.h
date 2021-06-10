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
    void SetScope(const String& scope) {
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
        s->print(F("["));
        s->print(scope);
        s->print(F("]: "));
      }
    }

    void print(const String& data, bool showScope) {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->print(data);
        delay(delayTime);
      }
    }
    void println(const String& data, bool showScope) {
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

    void println(const String& data) {
      this->println(data, true);
    }
    void println(const int& data) {
      this->println(data, true);
    }
    void print(const String& data) {
      this->print(data, true);
    }
    void print(const int& data) {
      this->print(data, true);
    }
  
  private:
    HardwareSerial* s;
    bool debugEnabled = false, scoped = false;
    int delayTime = 1000;
    String scope = "";
};

#endif
