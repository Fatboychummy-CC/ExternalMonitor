#include <Arduino.h>
#include "Constants.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"
#include "Debug.h"

void Debug::EnableDebugging() {
  debugEnabled = true;
}
void Debug::SetDebugDelay(int n) {
  delayTime = n;
}
void Debug::SetScope(char* scope) {
  scoped = true;
  strcpy(scope, scope);
}
char* Debug::GetScope() {
  return scope;
}
void Debug::ClearScope() {
  scoped = false;
}

void Debug::printScope() {
  if (scoped) {
    Serial.print(OPEN_BRACKET);
    Serial.print(scope);
    Serial.print(CLOSE_BRACKET);
    Serial.print(COLON);
    Serial.print(SPACE);
  }
}

template<typename T>
void Debug::print(const T& data, bool showScope) {
  if (debugEnabled) {
    if (showScope)
      printScope();
    Serial.print(data);
    delay(delayTime);
  }
}

template<typename T>
void Debug::println(const T& data, bool showScope) {
  if (debugEnabled) {
    if (showScope)
      printScope();
    Serial.println(data);
    delay(delayTime);
  }
}

void Debug::printRam(bool showScope) {
  int ram = freeRam();
  if (showScope) {
    // get the old scope.
    strcpy(scope, oldScope);

    // set new temporary scope
    SetScope(HEAP_TO_STACK_SCOPE);
    printScope();
    // print data
    Serial.println(ram);

    // return scope to old scope
    SetScope(oldScope);
  } else {
    // print data
    Serial.println(ram);
  }
}

void Debug::printMemory(bool showScope) {
  int mem = availableMemory();
  if (showScope) {
    // get the old scope.
    strcpy(scope, oldScope);

    // set new temporary scope
    SetScope(LARGEST_ALLOCATABLE_SCOPE);
    printScope();
    // print data
    Serial.println(mem);

    // return scope to old scope
    SetScope(oldScope);
  } else {
    // print data
    Serial.println(mem);
  }
}

bool Debug::debugEnabled = false;
bool Debug::scoped = false;
short Debug::delayTime = 1000;
