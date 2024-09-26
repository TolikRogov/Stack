#ifndef STACK_INCLUDE
#define STACK_INCLUDE

#include <stdio.h>
#include <stdlib.h>

typedef int Stack_elem_t;

enum StackStatusCode {
	STACK_NO_ERROR,
	STACK_ALLOC_ERROR,
	STACK_FILE_OPEN_ERROR,
	STACK_POINTER_ERROR,
	STACK_DIMENSIONS_ERROR
};

struct Stack_t {
	Stack_elem_t* data;
	size_t size;
	size_t capacity;
};

StackStatusCode StackCtor(Stack_t* stk);
StackStatusCode StackDtor(Stack_t* stk);
StackStatusCode StackVerify(Stack_t* stk);
StackStatusCode StackPush(Stack_t* stk, Stack_elem_t value);
StackStatusCode StackPop(Stack_t* stk, Stack_elem_t* value);

#endif //STACK_INCLUDE
