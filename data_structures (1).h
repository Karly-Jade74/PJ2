// karly obrien
// 1232791029

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct TAG_ELEMENT {
    int index; // index of  element
    double key; // key value of  element
    int pos; // index in the heap array, 0 if not in the heap
} ELEMENT;

typedef struct TAG_HEAP {
    int capacity; // capacity of the heap
    int size; // current size of the heap
    int *H; // array of indices to the ELEMENT array (1-based)
} HEAP;

#endif
