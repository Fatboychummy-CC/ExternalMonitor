#include <Arduino.h>
#include "FunctionStubsBecauseFuckCPlusPlus.h"

void InsertBuffer(char* buffer, const char* insert, byte pos, byte insertionSize, byte bufferSize) {
  // protect against out-of-bounds
  //   if the end of our string is going to be "further" than the end of the buffer,
  //   set the length of our string to be the end of the buffer, subtract by the position we're inserting at, subtract 1 for the null.
  if (pos + insertionSize >= bufferSize) insertionSize = bufferSize - pos - 1;

  // copy stuff from the insertion to the buffer
  for (byte i = pos; i < pos + insertionSize - 1; i++) {
    buffer[i] = insert[i - pos];
  }

  // Put null character at the end of the inserted string.
  buffer[pos + insertionSize] = 0;
}

void InsertBuffer(char* buffer, char* insert, byte pos, byte insertionSize, byte bufferSize) {
  // protect against out-of-bounds
  //   if the end of our string is going to be "further" than the end of the buffer,
  //   set the length of our string to be the end of the buffer, subtract by the position we're inserting at, subtract 1 for the null.
  if (pos + insertionSize >= bufferSize) insertionSize = bufferSize - pos - 1;

  // copy stuff from the insertion to the buffer
  for (byte i = pos; i < pos + insertionSize - 1; i++) {
    buffer[i] = insert[i - pos];
  }

  // Put null character at the end of the inserted string.
  buffer[pos + insertionSize] = 0;
}

void InsertBuffer(char* buffer, const char& insert, byte pos, byte insertionSize, byte bufferSize) {
  // protect against out-of-bounds
  //   if the end of our string is going to be "further" than the end of the buffer,
  //   set the length of our string to be the end of the buffer, subtract by the position we're inserting at, subtract 1 for the null.
  if (pos + insertionSize >= bufferSize) insertionSize = bufferSize - pos - 1;

  // copy stuff from the insertion to the buffer
  buffer[pos] = insert;

  // Put null character at the end of the inserted string.
  buffer[pos + insertionSize] = 0;
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
