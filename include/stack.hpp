#ifndef STACK_INCLUDE
#define STACK_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>

typedef int Stack_elem_t;

enum StackStatusCode {
	STACK_NO_ERROR,
	STACK_ALLOC_ERROR,
	STACK_FILE_OPEN_ERROR,
	STACK_FILE_CLOSE_ERROR,
	STACK_POINTER_ERROR,
	STACK_DATA_POINTER_ERROR,
	STACK_DIMENSIONS_ERROR,
	STACK_UNDERFLOW,
	STACK_EMPTY_ERROR
};

struct Stack_t {

#ifdef HTML_DUMP
	const char* stack_name;
	const char* file_name;
	const size_t line;
#endif

	Stack_elem_t* data;
	size_t size;
	size_t capacity;

	Log_Parts* log_parts;
};

StackStatusCode DoStackCtor(Stack_t* stk, size_t capacity);
StackStatusCode FilesCtor(Stack_t* stk);

StackStatusCode DoStackDtor(Stack_t* stk);
StackStatusCode FilesDtor(Stack_t* stk);

StackStatusCode DoStackVerify(Stack_t* stk);
StackStatusCode DoStackPush(Stack_t* stk, Stack_elem_t value);
StackStatusCode DoStackPop(Stack_t* stk, Stack_elem_t* value);

#endif //STACK_INCLUDE
