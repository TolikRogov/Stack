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

	StackStatusCode status = STACK_NO_ERROR;

	status = StackVerify(stk);
	STACK_ERROR_CHECK(status, stk);

	if (stk->size == stk->capacity) {
		stk->data = (Stack_elem_t*)realloc(stk->data, (stk->capacity *= 2) * sizeof(Stack_elem_t));
		if (!stk->data)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);
	}

	*(stk->data + stk->size++) = value;

	status = StackVerify(stk);
	STACK_ERROR_CHECK(status, stk);

	return STACK_NO_ERROR;
}

StackStatusCode StackPop(Stack_t* stk, Stack_elem_t* value) {

	StackStatusCode status = STACK_NO_ERROR;

	status = StackVerify(stk);
	STACK_ERROR_CHECK(status, stk);

	if (4 * stk->size < stk->capacity && stk->size > DEFAULT_CAPACITY) {
		stk->data = (Stack_elem_t*)realloc(stk->data, (stk->capacity = stk->size) * sizeof(Stack_elem_t));
		if (!stk->data)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);
	}

	*value = *(stk->data + (stk->size--) - 1);

	status = StackVerify(stk);
	STACK_ERROR_CHECK(status, stk);

	return STACK_NO_ERROR;
}

StackStatusCode StackVerify(Stack_t* stk) {

	if (!stk || !stk->data)
		STACK_ERROR_CHECK(STACK_POINTER_ERROR, stk);

	if (stk->capacity < 0 || stk->size < 0)
		STACK_ERROR_CHECK(STACK_DIMENSIONS_ERROR, stk)

	return STACK_NO_ERROR;
}

StackStatusCode StackDtor(Stack_t* stk) {

	stk->capacity = TRASH;
	stk->size 	  = TRASH;
	if (stk->data) {
		free(stk->data);
		stk->data = NULL;
	}

	printf("\n\033[32;6mDESTROY DONE!\033[0m\n\n");

	return STACK_NO_ERROR;
}
