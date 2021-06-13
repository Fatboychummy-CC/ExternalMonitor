#include <Arduino.h>
#include "LuaValue.h"
#include "FunctionStubsBecauseFuckCPlusPlus.h"

void InsertBuffer(char* buffer, const char* insert, byte pos, byte insertionSize, byte bufferSize) {
  // protect against out-of-bounds
  //   if the end of our string is going to be "further" than the end of the buffer,
  //   set the length of our string to be the end of the buffer, subtract by the position we're inserting at, subtract 1 for the null, subtract 1 for arrays starting at 0.
  if (pos + insertionSize >= bufferSize - 2) insertionSize = bufferSize - pos - 2;

  // copy stuff from the insertion to the buffer
  for (byte i = pos; i < pos + insertionSize; i++) {
    buffer[i] = insert[i - pos];
  }

  // Put null character at the end of the inserted string.
  buffer[pos + insertionSize] = 0;
}

void InsertBuffer(char* buffer, char* insert, byte pos, byte insertionSize, byte bufferSize) {
  // protect against out-of-bounds
  //   if the end of our string is going to be "further" than the end of the buffer,
  //   set the length of our string to be the end of the buffer, subtract by the position we're inserting at, subtract 1 for the null, subtract 1 for arrays starting at 0.
  if (pos + insertionSize >= bufferSize - 2) insertionSize = bufferSize - pos - 2;

  // copy stuff from the insertion to the buffer
  for (byte i = pos; i < pos + insertionSize; i++) {
    buffer[i] = insert[i - pos];
  }

  // Put null character at the end of the inserted string.
  buffer[pos + insertionSize] = 0;
}

void InsertBuffer(char* buffer, const char& insert, byte pos, byte bufferSize) {
  // protect against out-of-bounds
  //   if the end of our string is going to be "further" than the end of the buffer,
  //   return, because this is a 1-length string.
  if (pos + 1 >= bufferSize - 2) return;

  // copy stuff from the insertion to the buffer
  buffer[pos] = insert;

  // Put null character at the end of the inserted string.
  buffer[pos + 1] = 0;
}


bool BufferEqual(const char* b1, const char* b2, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    if (b1[i] != b2[i]) return false;
  }
  return true;
}

bool BufferEqual(char* b1, const char* b2, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    if (b1[i] != b2[i]) return false;
  }
  return true;
}

bool BufferEqual(const char* b1, char* b2, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    if (b1[i] != b2[i]) return false;
  }
  return true;
}

bool BufferEqual(char* b1, char* b2, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    if (b1[i] != b2[i]) return false;
  }
  return true;
}


int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void Zero(char* buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    buffer[i] = 0;
  }
}
