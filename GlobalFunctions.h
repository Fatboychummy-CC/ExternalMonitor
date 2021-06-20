#ifndef __FUCKCPLUSPLUS__
#define __FUCKCPLUSPLUS__

#include <Arduino.h>
#include "LuaValue.h"

void InsertBuffer(char* buffer, const char* insert, byte pos, byte insertionSize, byte bufferSize);
void InsertBuffer(char* buffer, char* insert, byte pos, byte insertionSize, byte bufferSize);
void InsertBuffer(char* buffer, const char& insert, byte pos, byte bufferSize);

bool BufferEqual(const char* b1, const char* b2, byte bufferSize);
bool BufferEqual(const char* b1, char* b2, byte bufferSize);
bool BufferEqual(char* b1, const char* b2, byte bufferSize);
bool BufferEqual(char* b1, char* b2, byte bufferSize);

int freeRam();

int availableMemory();

void Zero(char* buffer, byte bufferSize = LuaValue::MAX_ALLOC);

#endif
