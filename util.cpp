//karly obrien
//1232791029

#include <stdio.h>
#include <string.h>
#include "util.h"

int ReadInstruction(char *instrName, int *outIndex, double *outNewKey) {
    if (scanf("%s", instrName) != 1)
        return INSTR_STOP; 

    if (strcmp(instrName, "Stop") == 0)        return INSTR_STOP;
    if (strcmp(instrName, "Read") == 0)        return INSTR_READ;
    if (strcmp(instrName, "PrintArray") == 0)  return INSTR_PRINTARRAY;
    if (strcmp(instrName, "PrintHeap") == 0)   return INSTR_PRINTHEAP;
    if (strcmp(instrName, "BuildHeap") == 0)   return INSTR_BUILDHEAP;
    if (strcmp(instrName, "ExtractMin") == 0)  return INSTR_EXTRACTMIN;
    if (strcmp(instrName, "Write") == 0)       return INSTR_WRITE;

    if (strcmp(instrName, "Insert") == 0) {
        scanf("%d", outIndex);
        return INSTR_INSERT;
    }

    if (strcmp(instrName, "DecreaseKey") == 0) {
        scanf("%d %lf", outIndex, outNewKey);
        return INSTR_DECREASEKEY;
    }

    return INSTR_UNKNOWN;
}

void PrintArray(ELEMENT **V, int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d %lf %d\n", V[i]->index, V[i]->key, V[i]->pos);
    }
}
