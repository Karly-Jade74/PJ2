// karly obrien
// 1232791029

#ifndef UTIL_H
#define UTIL_H

#include "data_structures.h"

// Instruction constants
#define INSTR_STOP         0
#define INSTR_READ         1
#define INSTR_PRINTARRAY   2
#define INSTR_PRINTHEAP    3
#define INSTR_BUILDHEAP    4
#define INSTR_INSERT       5
#define INSTR_EXTRACTMIN   6
#define INSTR_DECREASEKEY  7
#define INSTR_WRITE        8
#define INSTR_UNKNOWN     -1

// Returns one of the INSTR_* constants.
int ReadInstruction(char *instrName, int *outIndex, double *outNewKey);
// Print array V (1..n) to stdout
void PrintArray(ELEMENT **V, int n);
#endif
