#include "../include/utilities.hpp"

StackStatusCode StackCtor(Stack_t* stk) {

	stk->capacity = DEFAULT_CAPACITY;
	stk->data = (Stack_elem_t*)calloc(stk->capacity, sizeof(Stack_elem_t));
	if (!stk->data)
		STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);
	stk->size = 0;

	return STACK_NO_ERROR;
}

StackStatusCode StackPush(Stack_t* stk, Stack_elem_t value) {

	if (stk->size == stk->capacity) {
		stk->data = (Stack_elem_t*)realloc(stk->data, (stk->capacity *= 2) * sizeof(Stack_elem_t));
		if (!stk->data)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);
	}

	*(stk->data + stk->size) = value;

	return STACK_NO_ERROR;
}

StackStatusCode StackDtor(Stack_t* stk) {

	stk->capacity = 0;
	stk->size 	  = 0;
	if (stk->data) {
		free(stk->data);
		stk->data = NULL;
	}

	printf("DESTROY DONE!\n");

	return STACK_NO_ERROR;
}
