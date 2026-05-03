#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef int type;
typedef struct Stack Stack;

Stack* init(size_t start_size);

int push(Stack* stack, type value);

int pop(Stack* stack);

int top(Stack* stack, type* value);

int size(Stack* stack, size_t* size);

void clear(Stack* stack);

int empty(Stack* stack);

int check_canaries(Stack* stack, int* out);

int check_hash(Stack* stack, int* out);

#endif