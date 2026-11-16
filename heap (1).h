//karly obrien
//1232791029

#ifndef HEAP_H
#define HEAP_H
#include "data_structures.h"

HEAP* CreateHeap(int capacity);
// Min-Heapify at position pos 
void Heapify(HEAP *pHeap, ELEMENT **V, int pos);
// Build min heap from all elements in V 
void BuildHeap(HEAP *pHeap, ELEMENT **V, int n);
// Insert element V[index] into the heap
void HeapInsert(HEAP *pHeap, ELEMENT **V, int index);
// Extract the minimum element from the heap; returns index of extracted element
int ExtractMin(HEAP *pHeap, ELEMENT **V);
// Decrease key of V[index] to newKey and restore heap property
void DecreaseKey(HEAP *pHeap, ELEMENT **V, int index, double newKey);
// Print heap contents to stdout
void PrintHeap(HEAP *pHeap);
#endif
