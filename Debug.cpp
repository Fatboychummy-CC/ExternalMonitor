#include <Arduino.h>
#include "Constants.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"
#include "Debug.h"

bool Debug::debugEnabled = false;
bool Debug::scoped = false;
short Debug::delayTime = 1000;
char Debug::oldScope[30];
char Debug::scope[30];

void Debug::EnableDebugging() {
  debugEnabled = true;
}
void Debug::SetDebugDelay(int n) {
  delayTime = n;
}
void Debug::SetScope(char* _scope) {
  scoped = true;
  strcpy(scope, _scope);
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
