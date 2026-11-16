# PJ2
Project 2 from 310 Data Structures
CSE310 Project 2: Priority Queues

**1 Data Structures and Functions
In class, we studied the max heap data structure and the basic max heap functions Heapify,
BuildHeap, ExtractMax, IncreaseKey, and Insertion. Symmetrically, we have the min heap
data structure (in which the key value at a node cannot be smaller than the value at its parent)
and the corresponding basic min heap functions Heapify, BuildHeap, ExtractMin, DecreaseKey,
and Insertion. In this project, you will implement the min heap data structure.
1.1 Data Types
The project description will make reference to the following two data types. You may use them
with modifications.
typedef struct TAG_ELEMENT{
int index; // index of the element
double key; // key value of the element
int pos; // index in the heap-array, 0 if not in the heap
// Other fields as you see fit
}ELEMENT;
typedef struct TAG_HEAP{
int capacity; // capacity of the heap
1
int size; // current size of the heap
// int *H; // array of pointers to indices of the ELEMENT array
int *H; // array of indices to the ELEMENT array
// Other fields as you see fit
}HEAP;
With the declaration
ELEMENT **V;
HEAP *pHeap;
you declare V as a pointer to pointer to ELEMENT, and pHeap as a pointer to HEAP. With properly
dynamic memory allocation, you can use V as an array of pointers to ELEMENT. Then V[i] is a
pointer to ELEMENT.
In this project, you need to work with both V and pHeap. If V[i]->pos is 0, the element pointed
to by V[i] is not on pHeap. Otherwise, the element pointed to by V[i] is on the pHeap. More
importantly, for any i such that V[i]->pos > 0 we have
pHeap->H[V[i]->pos] == i.
For any k between 1 and pHeap->size, we have
V[pHeap->H[k]]->pos == k.
In class, for ease of presentation, we presented the functions for max heap under the assumption
that A[i] is of type int for each valid index i. A[i] is also used as the key in the heap operations.
In this project, the key of the k-th element in the heap array is V[pHeap->H[k]]->key.

**2 Modular Design
You will continue to do modular design, using the provided Makefile to compile various modules
to generate the executable file named PJ2. You need to have exactly the following modules:
1. data_structures.h
which defines the data types described in Section 1.1 or their equivalent.
2. main.h and main.cpp, which coordinate all modules;
3. util.h and util.cpp, which provide utility services including the recognition of various
instructions;
4. heap.h and heap.cpp, which implement the functions for min heap.
2

**3 Flow of the Project
3.1 Valid Execution
A valid execution of your project has the following form:
./PJ2 <I-File> <O-File>
where ./PJ2 tells the system to search for the executable file PJ2 in the current directory, <I-File>
is the input file, and <O-File> is the output file.
Your program should check whether the execution is valid. If the execution is not valid, your
program should print out the following message to stderr and stop.
Usage: ./PJ2 <I-File> <O-File>
<I-File> is the input file
<O-File> is the output file
Note that your program should not crash when the execution is not valid.
Upon a valid execution, your program should expect the following instructions from stdin and
act accordingly:
• Stop:
On reading Stop, the program should write the following to stdout and stop.
Instruction: Stop
• Read:
On reading Read, the program should do the following.
1. Write the following line to stdout:
Instruction: Read
2. Open the file argv[1] in read mode. We will call this file the input file.
If the file is not opened successfully, write an error message to stderr and wait for the
next instruction from stdin, skipping the following actions.
3. Read in the first integer, n, from the input file.
Perform proper memory allocation so that V can be used as an array name, and allocate
memory for V[i] so that we can access the fields of V[i] for i=1, 2, ..., n. For each
value of i=1, 2, ..., n, read in key i from the input file; set
3
V[i]->index = i;
V[i]->key = key_i;
V[i]->pos = 0;
4. Close the file argv[1].
5. Perform proper memory allocation so that pHeap points to a HEAP with capacity equal
to n and size equal to 0.
6. Wait for the next instruction from stdin.
• PrintArray:
On reading PrintArray, the program should do the following.
1. Write the following line to stdout:
Instruction: PrintArray
2. If the array V is NULL, print the following error message to stderr:
Error: array is NULL
then wait for the next instruction from stdin, skipping the following action(s).
3. If the array V is not NULL, print the current state of the array to stdout then wait for
the next instruction from stdin.
When the array V is not NULL, the program writes to stdout the index of the array, followed
by the key, followed by the pos (refer to posted test cases for output format).
• PrintHeap:
On reading PrintHeap, the program should do the following.
1. Write the following line to stdout:
Instruction: PrintHeap
2. If the heap is NULL, print the following error message to stderr:
Error: heap is NULL
then wait for the next instruction from stdin, skipping the following action(s).
3. If the heap is not NULL, print the current state of the heap to stdout then wait for the
next instruction from stdin.
When the heap is not NULL, the program writes the heap information to stdout (refer to
posted test cases for output format).
• BuildHeap:
On reading BuildHeap, the program should do the following.
1. Write the following line to stdout:
Instruction: BuildHeap
2. Set the size of the heap pointed to by pHeap to the number of elements in array V. For
i = 1 to n do the following
V[i]->pos = i;
pHeap->H[i] = i;
Then apply the linear-time BuildHeap algorithm taught in class.
3. Wait for the next instruction from stdin.
When the heap is not NULL, the program writes the heap information to stdout (refer to
posted test cases for output format).
• Insert <index>:
On reading Insert <index>, the program should do the following.
1. Write the following line to stdout:
Instruction: Insert <index>
where int is printed using the ”%d” format.
2. If index is not within 1 and n, write the following to stderr:
Error: index out of bound
then wait for the next instruction from stdin, skipping the following actions.
3. If V[index]->pos != 0, write the following to stderr:
Error: V[index] already in the heap
then wait for the next instruction from stdin, skipping the following actions.
4. Insert V[index] into the heap. You start with the following statements:
pHeap->size = pHeap->size+1;
pHeap->H[pHeap->size] = index;
V[index]->pos = pHeap->size;
then make proper heap operations related to insertion. Write the following line to stdout:
Element V[index] inserted into the heap
where <index> (the index of the heap array where the element is inserted) is printed
using the ”%d” format.
5. Wait for the next instruction from stdin.
• ExtractMin:
On reading ExtractMin, the program should do the following.
1. Write the following line to stdout:
Instruction: ExtractMin
2. If the heap is NULL, print the following error message to stderr:
Error: heap is NULL
then wait for the next instruction from stdin, skipping the following actions.
3. If the heap is empty, print the following error message to stderr:
Error: heap is empty
then wait for the next instruction from stdin, skipping the following actions.
4. Perform the ExtractMin operation. Before the ExtractMin operation, we should have
V[pHeap->H[1]]->pos == 1. Therefore V[pHeap->H[1]] is the element to be extracted
from the heap.
5. Wait for the next instruction from stdin.
• DecreaseKey <index> <NewKey>:
On reading DecreaseKey <index> <NewKey>, the program should do the following.
1. Write the following line to stdout:
Instruction: DecreaseKey <index> <NewKey>
where int is printed using the ”%d” format and double is printed using the ”%lf” format.
6
2. If <index> is out of range or <NewKey> is not smaller than the current key, print the
following error message to stderr:
Error: invalid call to DecreaseKey
then wait for the next instruction from stdin, skipping the following actions.
3. If V[index]->pos == 0, write the following to stderr:
Error: V[index] not in the heap
then wait for the next instruction from stdin, skipping the following actions.
4. Decrease the key field of the corresponding object to <NewKey> and perform the corre-
sponding operations on the min heap.
5. Wait for the next instruction from stdin.
• Write:
On reading Write, the program should do the following.
1. Write the following line to stdout:
Instruction: Write
2. Opens the file argv[2] in write mode.
If the file is not opened successfully, write an error message to stderr and wait for the
next instruction from stdin, skipping the following actions.
3. Write the array information (about V) to the output file. It should write n lines to the
output file, where the i-th line contains
i V[i]->key V[i]->pos
where int is printed using the ”%d” format and double is printed using the ”%lf” format,
with exactly one white space between values (refer to posted test cases for format).
4. Close the output file argv[2].
5. Wait for the next instruction from stdin.
• Unknown Instructions:
If your program reads in an unknown instruction (other than the ones listed in the above),
the program should do the following.
1. Write the following message to stdout
7
Warning: Invalid instruction
2. Wait for the next instruction from stdin.

**4 Format of the Input File
The input file specified by argv[1] is an ascii file. It contains an integer n, followed by n real
numbers, where two numbers are separated by one or more white spaces. Here a white space is
either a space (with ascii value 32), a tab (with ASCII value 9), or a newline (with ASCII value 10).
In other words, it is one of the three characters in the set
{’ ’, ’\t’, ’\n’}.
The first integer, call it n, is the number of elements. The next n real numbers are the key value of
the first element, the key value of the second element, . . . , the key value of the n-th element. An
example input file input has the following content.
9
9 8 7
6
5
4
3 2 1
It contains the same information as the following file:
9
9.00
8
7
6
5
4
3
2
1
8

**5 Output Format
When writing an int, use the ”%d” format. When writing a double, use the ”%lf” format. When
writing multiple values in the same line, use exactly one space between values, here space has ASCII
value 32
