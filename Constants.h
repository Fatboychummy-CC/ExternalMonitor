#ifndef __CONSTANTS__
#define __CONSTANTS__

// various characters
const char OPEN_BRACE    = '{';
const char CLOSE_BRACE   = '}';
const char OPEN_BRACKET  = '[';
const char CLOSE_BRACKET = ']';
const char COMMA         = ',';
const char QUOTE         = '"';
const char CHEVRON       = '>';
const char UNDERSCORE    = '_';
const char SPACE         = ' ';
const char SEMICOLON     = ';';
const char COLON         = ':';
const char BACKSLASH     = '\\';

const char OP[]     = "OP     : ";
const char N_ARGS[] = "NUMARGS: ";
const char ARG[]    = "ARG    : ";
const char CTYPE[]  = "CTYPE  : ";
const char DATA[]   = "DATA   : ";
const char OUT[]    = "OUTPUT : ";

const char LOOP_SCOPE[]        = "Loop";
const char ARG_LOOP_SCOPE[]    = "ArgLoop";
const char RUN_COMMAND_SCOPE[] = "RunCommand";
const char BLINK_SCOPE[]       = "Blink";

const char BAD_ARG[]         = "BadArg";
const char BAD_ARGUMENTS[]   = "Bad arguments.";
const char NULL_COMMAND[]    = "Null Command.";
const char UNKNOWN_COMMAND[] = "Unknown command.";

const char UNAVAILABLE[]   = "This method is currently unavailable.";
const char NO_CONNECTION[] = "Not connected.";

const char LARGEST_ALLOCATABLE_SCOPE[] = " LARGEST ALLOCATABLE ";
const char HEAP_TO_STACK_SCOPE[]       = "HEAP<->STACK DISTANCE";

const char SERIALIZE_FAIL[] = "\"Failed to serialize.\"";
const byte SERIALIZE_FAIL_LEN = 22;

#endif
