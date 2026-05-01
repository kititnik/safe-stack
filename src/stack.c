#include "stack.h"
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

const char* NULL_STACK_POINTER_ERROR = "Pointer to stack is null";
const char* VALUE_POINTER_NULL_ERROR = "Pointer to argumet value is null";
const char* STACK_ALLOCATION_ERROR = "Failed to allocate stack memory";
const char* RESIZE_ERROR = "An error occured while stack resize.\n Last capacity = %zu.\n Capacity resize attempt = %zu";
const char* PUSH_STACK_OVERFLOW_ERROR = "Stack overflow while push attempt";
const char* INCORRECT_START_CAPACITY_ERROR = "Incorrect stack start size!";
const char* EMPTY_STACK_POP_ERROR = "Error: Attempt to pop from empty stack";
const char* EMPTY_STACK_TOP_ERROR = "Error: Attempt to top from empty stack";

struct Stack {
    size_t capacity;
    size_t size;
    type* data;

    uint64_t hash;
    uint64_t base;
    uint64_t inv_base;
};

uint64_t generate_base() {
    uint64_t base = ((uint64_t)rand() << 33) ^ ((uint64_t)rand() << 1) ^ 1ULL;
    return base;
}

uint64_t compute_inv_base(uint64_t base) {
    uint64_t inv_base = 1;
    for(int i = 0; i < 6; i++) {
        inv_base *= 2-base*inv_base;
    }
    return inv_base;
}

void push_update_hash(Stack* stack, type value) {
    stack->hash = stack->hash * stack->base + (uint64_t)value;
}

void pop_update_hash(Stack* stack, type value) {
    stack->hash = (stack->hash - (uint64_t)value) * stack->inv_base;
}

int check_integrity(Stack* stack, int* out) {
    if(stack == NULL) {
        fprintf(stderr, "%s", NULL_STACK_POINTER_ERROR);
        return EXIT_FAILURE;
    }
    uint64_t hash = 0;
    for(int i = 0; i < stack->size; i++) {
        hash = hash * stack->base + (uint64_t)stack->data[i];
    }
    *out = (hash == stack->hash);
    return EXIT_FAILURE;
}

Stack* init(size_t start_capacity) {
    if(start_capacity < 1) {
        fprintf(stderr, "%s", INCORRECT_START_CAPACITY_ERROR);
        return NULL;
    }
    Stack* stack = malloc(sizeof(Stack));
    if(stack == NULL) {
        fprintf(stderr, "%s", STACK_ALLOCATION_ERROR);
        return NULL;
    }
    stack->capacity = start_capacity;
    stack->data = calloc(start_capacity, sizeof(type));
    if(stack->data == NULL) {
        fprintf(stderr, "%s", STACK_ALLOCATION_ERROR);
        return NULL;
    }
    stack->size = 0;
    stack->base = generate_base();
    stack->inv_base = compute_inv_base(stack->base);
    return stack;
}

int resize(Stack* stack) {
    if(stack == NULL) {
        fprintf(stderr, "%s", NULL_STACK_POINTER_ERROR);
        return EXIT_FAILURE;
    }
    size_t past_capacity = stack->capacity;
    size_t new_capacity = past_capacity*2;
    void* ptr = realloc(stack->data, new_capacity);
    if(ptr == NULL) {
        fprintf(stderr, RESIZE_ERROR, past_capacity, new_capacity);
        return EXIT_FAILURE;
    }
    stack->data = ptr;
    stack->capacity = new_capacity;
    return EXIT_SUCCESS;
}

int push(Stack* stack, type value) {
    if(stack == NULL) {
        fprintf(stderr, "%s", NULL_STACK_POINTER_ERROR);
        return EXIT_FAILURE;
    }
    if(stack->size == stack->capacity) {
        int code = resize(stack);
        if(code == EXIT_FAILURE) {
            fprintf(stderr, "%s", PUSH_STACK_OVERFLOW_ERROR);
            return EXIT_FAILURE;
        }
    }
    stack->data[stack->size] = value;
    push_update_hash(stack, value);
    stack->size++;
    return EXIT_SUCCESS;
}

int pop(Stack* stack) {
    if(stack == NULL) {
        fprintf(stderr, "%s", NULL_STACK_POINTER_ERROR);
        return EXIT_FAILURE;
    }
    if(empty(stack)) {
        fprintf(stderr, "%s", EMPTY_STACK_POP_ERROR);
        return EXIT_FAILURE;
    }
    type value = stack->data[stack->size-1];
    pop_update_hash(stack, value);
    stack->size--;
    
    return EXIT_SUCCESS;
}

int top(Stack* stack, type* value) {
    if(stack == NULL) {
        fprintf(stderr, "%s", NULL_STACK_POINTER_ERROR);
        return EXIT_FAILURE;
    }
    if(value == NULL) {
        fprintf(stderr, "%s", VALUE_POINTER_NULL_ERROR);
        return EXIT_FAILURE;
    }
    if(empty(stack)) {
        fprintf(stderr, "%s", EMPTY_STACK_TOP_ERROR);
        return EXIT_FAILURE;
    }
    *value = stack->data[stack->size-1];
    return EXIT_SUCCESS;
}

int size(Stack* stack, size_t* size) {
    if(stack == NULL) {
        fprintf(stderr, "%s", NULL_STACK_POINTER_ERROR);
        return EXIT_FAILURE;
    }
    if(size == NULL) {
        fprintf(stderr, "%s", VALUE_POINTER_NULL_ERROR);
        return EXIT_FAILURE;
    }
    *size = stack->size;
    return EXIT_SUCCESS;
}

void clear(Stack* stack) {
    if(stack == NULL) {
        fprintf(stderr, "%s", NULL_STACK_POINTER_ERROR);
        return;
    }
    free(stack->data);
    free(stack);
}

int empty(Stack* stack) {
    if(stack == NULL) {
        fprintf(stderr, "%s", NULL_STACK_POINTER_ERROR);
        return -1;
    }
    return (stack->size == 0);
}