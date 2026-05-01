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