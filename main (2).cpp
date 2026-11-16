// Name: Karly O'Brien
// ASU ID: 1232791029

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./PJ2 <I-File> <O-File>\n");
        fprintf(stderr, "<I-File> is the input file\n");
        fprintf(stderr, "<O-File> is the output file\n");
        return 1;
    }

    ELEMENT **V = NULL; // array of pointers to element
    HEAP *pHeap = NULL; // pointer to the heap
    int n = 0;  // number of elements

    char   instrName[64];
    int    instrIndex  = 0;
    double instrNewKey = 0.0;

    while (1) {
        int instr = ReadInstruction(instrName, &instrIndex, &instrNewKey);
         // Stop 
        if (instr == INSTR_STOP) {
            printf("Instruction: Stop\n");
            break;
        }
        // Read 
        else if (instr == INSTR_READ) {
            printf("Instruction: Read\n");
            FILE *fp = fopen(argv[1], "r");
            if (!fp) {
                fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
                continue;
            }

            fscanf(fp, "%d", &n);
            V = (ELEMENT**)malloc((n + 1) * sizeof(ELEMENT*));
            for (int i = 1; i <= n; i++) {
                V[i] = (ELEMENT*)malloc(sizeof(ELEMENT));
                double key_i;
                fscanf(fp, "%lf", &key_i);
                V[i]->index = i;
                V[i]->key   = key_i;
                V[i]->pos   = 0;
            }
            fclose(fp);
            // Allocate heap with capacity n and size 0
            pHeap = CreateHeap(n);
        }

        // PrintArray 
        else if (instr == INSTR_PRINTARRAY) {
            printf("Instruction: PrintArray\n");
            if (V == NULL) {
                fprintf(stderr, "Error: array is NULL\n");
                continue;
            }
            PrintArray(V, n);
        }

        // Print Heap
        else if (instr == INSTR_PRINTHEAP) {
            printf("Instruction: PrintHeap\n");
            if (pHeap == NULL) {
                fprintf(stderr, "Error: heap is NULL\n");
                continue;
            }
            PrintHeap(pHeap);
        }

        // Build Heap
        else if (instr == INSTR_BUILDHEAP) {
            printf("Instruction: BuildHeap\n");
            BuildHeap(pHeap, V, n);
        }

        // Insert <index> 
        else if (instr == INSTR_INSERT) {
            printf("Instruction: Insert %d\n", instrIndex);

            if (instrIndex < 1 || instrIndex > n) {
                fprintf(stderr, "Error: index out of bound\n");
                continue;
            }
            if (V[instrIndex]->pos != 0) {
                fprintf(stderr, "Error: V[%d] already in the heap\n", instrIndex);
                continue;
            }

            // Set up per spec, calls HeapInsert to bubble up
            pHeap->size++;
            pHeap->H[pHeap->size] = instrIndex;
            V[instrIndex]->pos    = pHeap->size;
            HeapInsert(pHeap, V, instrIndex);
            printf("Element V[%d] inserted into the heap\n", instrIndex);
        }

        // ExtractMin
        else if (instr == INSTR_EXTRACTMIN) {
            printf("Instruction: ExtractMin\n");

            if (pHeap == NULL) {
                fprintf(stderr, "Error: heap is NULL\n");
                continue;
            }
            if (pHeap->size == 0) {
                fprintf(stderr, "Error: heap is empty\n");
                continue;
            }
            ExtractMin(pHeap, V);
        }

        //  Decrease Key <index> <NewKey> 
        else if (instr == INSTR_DECREASEKEY) {
            printf("Instruction: DecreaseKey %d %lf\n", instrIndex, instrNewKey);

            // Check index range and that newKey < current key
            if (instrIndex < 1 || instrIndex > n ||
                instrNewKey >= V[instrIndex]->key) {
                fprintf(stderr, "Error: invalid call to DecreaseKey\n");
                continue;
            }
            if (V[instrIndex]->pos == 0) {
                fprintf(stderr, "Error: V[%d] not in the heap\n", instrIndex);
                continue;
            }

            DecreaseKey(pHeap, V, instrIndex, instrNewKey);
        }

        //  Write 
        else if (instr == INSTR_WRITE) {
            printf("Instruction: Write\n");

            FILE *fp = fopen(argv[2], "w");
            if (!fp) {
                fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
                continue;
            }

            for (int i = 1; i <= n; i++) {
                fprintf(fp, "%d %lf %d\n", V[i]->index, V[i]->key, V[i]->pos);
            }
            fclose(fp);
        }

        // Unknown instruction
        else {
            printf("Warning: Invalid instruction\n");
        }
    }

    // Free memory
    if (V != NULL) {
        for (int i = 1; i <= n; i++)
            free(V[i]);
        free(V);
    }
    if (pHeap != NULL) {
        free(pHeap->H);
        free(pHeap);
    }

    return 0;
}
