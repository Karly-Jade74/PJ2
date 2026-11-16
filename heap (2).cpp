// Name: Karly
// ASU ID: 1232791029

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

static void SwapHeap(HEAP *pHeap, ELEMENT **V, int i, int j) {
    int tmp = pHeap->H[i];
    pHeap->H[i] = pHeap->H[j];
    pHeap->H[j] = tmp;
    V[pHeap->H[i]]->pos = i;
    V[pHeap->H[j]]->pos = j;
}

// Allocates a new heap with given capacity 
HEAP* CreateHeap(int capacity) {
    HEAP *pHeap = (HEAP*)malloc(sizeof(HEAP));
    pHeap->capacity = capacity;
    pHeap->size = 0;
    pHeap->H = (int*)malloc((capacity + 1) * sizeof(int));
    return pHeap;
}

// Sifts down at position pos to restore min heap property
void Heapify(HEAP *pHeap, ELEMENT **V, int pos) {
    int smallest = pos;
    int left  = 2 * pos;
    int right = 2 * pos + 1;
    if (left <= pHeap->size &&
        V[pHeap->H[left]]->key < V[pHeap->H[smallest]]->key)
        smallest = left;
    if (right <= pHeap->size &&
        V[pHeap->H[right]]->key < V[pHeap->H[smallest]]->key)
        smallest = right;
    if (smallest != pos) {
        SwapHeap(pHeap, V, pos, smallest);
        Heapify(pHeap, V, smallest);
    }
}

// Build min heap in linear time 
void BuildHeap(HEAP *pHeap, ELEMENT **V, int n) {
    // Set up heap array: H[i] = i, V[i]->pos = i
    pHeap->size = n;
    for (int i = 1; i <= n; i++) {
        pHeap->H[i] = i;
        V[i]->pos = i;
    }
    // Heapify from bottom up
    for (int i = n / 2; i >= 1; i--) {
        Heapify(pHeap, V, i);
    }
}

// We just bubble up
void HeapInsert(HEAP *pHeap, ELEMENT **V, int index) {
    int pos = V[index]->pos; 
    while (pos > 1) {
        int parent = pos / 2;
        if (V[pHeap->H[parent]]->key > V[pHeap->H[pos]]->key) {
            SwapHeap(pHeap, V, parent, pos);
            pos = parent;
        } else {
            break;
        }
    }
}

int ExtractMin(HEAP *pHeap, ELEMENT **V) {
    int minIndex = pHeap->H[1]; 
    pHeap->H[1] = pHeap->H[pHeap->size];
    V[pHeap->H[1]]->pos = 1;
    V[minIndex]->pos = 0;
    pHeap->size--;
    if (pHeap->size > 0)
        Heapify(pHeap, V, 1);

    return minIndex;
}

// DecreaseKey
void DecreaseKey(HEAP *pHeap, ELEMENT **V, int index, double newKey) {
    V[index]->key = newKey;
    int pos = V[index]->pos;

    // Bubble up
    while (pos > 1) {
        int parent = pos / 2;
        if (V[pHeap->H[parent]]->key > V[pHeap->H[pos]]->key) {
            SwapHeap(pHeap, V, parent, pos);
            pos = parent;
        } else {
            break;
        }
    }
}

// Print heap to stdout
void PrintHeap(HEAP *pHeap) {
    printf("Capacity = %d, size = %d\n", pHeap->capacity, pHeap->size);
    for (int i = 1; i <= pHeap->size; i++) {
        printf("H[%d] = %d\n", i, pHeap->H[i]);
    }
}
