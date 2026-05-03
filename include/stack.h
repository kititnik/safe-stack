#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef int type;
typedef struct Stack Stack;

/** Allocates and initializes a stack. Returns NULL on failure or start_capacity < 1. */
Stack* init(size_t start_size);

/** Pushes value into the stack, resizing if needed. */
int push(Stack* stack, type value);

/** Removes the top element. Fails on empty stack. */
int pop(Stack* stack);

/** Writes the top element into *value without removing it. Fails on empty stack or NULL value. */
int top(Stack* stack, type* value);

/** Writes the current number of elements into *size. */
int size(Stack* stack, size_t* size);

/** Frees all memory. The pointer is invalid after this call. */
void clear(Stack* stack);

/** Returns 1 if empty, 0 if not, -1 on error. */
int empty(Stack* stack);

/** O(1). Writes 1 into *out if canaries are correct, 0 if corrupted. */
int check_canaries(Stack* stack, int* out);

/** O(n). Recomputes hash. Writes 1 into *out if valid, 0 if corrupted. */
int check_hash(Stack* stack, int* out);

#endif