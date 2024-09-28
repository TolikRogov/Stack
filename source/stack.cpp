#include "../include/utilities.hpp"

StackStatusCode DoStackCtor(Stack_t* stk, size_t capacity) {

#ifdef HTML_DUMP
	StackStatusCode status = STACK_NO_ERROR;

	status = DirCtor(stk);
	STACK_ERROR_CHECK(status, stk);

	status = HtmlLogStarter(stk);
	STACK_ERROR_CHECK(status, stk);
#endif

	stk->capacity = (capacity < DEFAULT_CAPACITY && capacity != 0 ? DEFAULT_CAPACITY : capacity);

	if (stk->capacity) {
		stk->data = (Stack_elem_t*)calloc(stk->capacity, sizeof(Stack_elem_t));
		if (!stk->data)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);
	}

	stk->size = 0;

	return STACK_NO_ERROR;
}

StackStatusCode DoStackPush(Stack_t* stk, Stack_elem_t value) {

	StackStatusCode status = STACK_NO_ERROR;

	STACK_VERIFY(stk);

	if (stk->size == stk->capacity) {
		stk->data = (Stack_elem_t*)realloc(stk->data, (stk->capacity *= 2) * sizeof(Stack_elem_t));
		if (!stk->data)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);
	}

	*(stk->data + stk->size++) = value;

	STACK_VERIFY(stk);

	return STACK_NO_ERROR;
}

StackStatusCode DoStackPop(Stack_t* stk, Stack_elem_t* value) {

	StackStatusCode status = STACK_NO_ERROR;

	STACK_VERIFY(stk);

	if (4 * stk->size < stk->capacity && stk->size > DEFAULT_CAPACITY) {
		stk->data = (Stack_elem_t*)realloc(stk->data, (stk->capacity = stk->size) * sizeof(Stack_elem_t));
		if (!stk->data)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);
	}

	if (!stk->size)
		STACK_ERROR_CHECK(STACK_EMPTY_ERROR, stk);

	*value = *(stk->data + (stk->size--) - 1);

	STACK_VERIFY(stk);

	return STACK_NO_ERROR;
}

StackStatusCode DoStackVerify(Stack_t* stk) {

	if (!stk)
		return STACK_POINTER_ERROR;

	if (!stk->capacity && !stk->size && !stk->data)
		return STACK_UNDERFLOW;

	if (!stk->data)
		return STACK_DATA_POINTER_ERROR;

	if (stk->capacity < 0 || stk->size < 0 || stk->size > stk->capacity)
		return STACK_DIMENSIONS_ERROR;

	return STACK_NO_ERROR;
}

StackStatusCode DoStackDtor(Stack_t* stk) {

	StackStatusCode status = STACK_NO_ERROR;

	STACK_VERIFY(stk);

#ifdef HTML_DUMP
	status = HtmlLogFinisher(stk);
	STACK_ERROR_CHECK(status, stk);
#endif

	stk->capacity = TRASH;
	stk->size 	  = TRASH;

	if (stk->data) {
		free(stk->data);
		stk->data = NULL;
	}

	printf("\n" GREEN("ALLOCATED MEMORY FREED!") "\n\n");

	return STACK_NO_ERROR;
}
