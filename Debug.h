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
        s->print(SEMICOLON);
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
    void println(T data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->println(data);
        delay(delayTime);
      }
    }

    template<typename T>
    void print(T data) const {
      this->print(data, true);
    }

    template<typename T>
    void println(T data) const {
      this->println(data, true);
    }

    /*
    void print(String& data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->print(data);
        delay(delayTime);
      }
    }
    void println(String& data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->println(data);
        delay(delayTime);
      }
    }

    void print(char* data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->print(data);
        delay(delayTime);
      }
    }
    void println(char* data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->println(data);
        delay(delayTime);
      }
    }
    void print(const char* data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->print(data);
        delay(delayTime);
      }
    }
    void println(const char* data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->println(data);
        delay(delayTime);
      }
    }
    void print(const int& data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->print(data);
        delay(delayTime);
      }
    }
    void println(const int& data, bool showScope) const {
      if (debugEnabled) {
        if (showScope)
          this->printScope();
        s->println(data);
        delay(delayTime);
      }
    }

    void println(const String& data) const {
      this->println(data, true);
    }
    void print(const String& data) const {
      this->print(data, true);
    }

    void println(char* data) const {
      this->println(data, true);
    }
    void println(const int& data) const {
      this->println(data, true);
    }
    void print(char* data) const {
      this->print(data, true);
    }
    void print(const int& data) const {
      this->print(data, true);
    }

    void println(const char* data) const {
      this->println(data, true);
    }
    void print(const char* data) const {
      this->print(data, true);
    }
    */

  private:
    HardwareSerial* s;
    bool debugEnabled = false, scoped = false;
    short delayTime = 1000;
    char scope[30];
};

#endif
