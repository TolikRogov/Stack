#include "../include/utilities.hpp"

StackStatusCode DoStackCtor(Stack_t* stk, size_t capacity) {

	StackStatusCode status = STACK_NO_ERROR;

	if (!stk)
		STACK_ERROR_CHECK(STACK_POINTER_ERROR, stk);

#ifdef CANARY_PROTECTION
	stk->canary1 = STACK_CANARY_HEX;
	stk->canary2 = STACK_CANARY_HEX;
#endif

	stk->capacity = (capacity < DEFAULT_CAPACITY && capacity != 0 ? DEFAULT_CAPACITY : capacity);

#ifdef CANARY_PROTECTION
	size_t size = stk->capacity * sizeof(Stack_elem_t) + 2 * sizeof(Canary_t);
	stk->data = (Stack_elem_t*)((char*)calloc(1, size + (ALIGNMENT - size % ALIGNMENT)) + sizeof(Canary_t));
	if (!stk->data)
		STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);

	*(Canary_t*)((char*)stk->data - sizeof(Canary_t)) = DATA_CANARY_HEX;
	*(Canary_t*)((char*)stk->data + stk->capacity * sizeof(Stack_elem_t)) = DATA_CANARY_HEX;

	StackMemset(stk, 0, stk->capacity, POISON);
#else
	if (stk->capacity != 0) {
		stk->data = (Stack_elem_t*)calloc(stk->capacity, sizeof(Stack_elem_t));
		if (!stk->data)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);
		StackMemset(stk, 0, stk->capacity, POISON);
	}
#endif

	stk->size = 0;

#ifdef HTML_DUMP
	status = DirCtor(stk);
	STACK_ERROR_CHECK(status, stk);

	status = HtmlLogStarter(stk);
	STACK_ERROR_CHECK(status, stk);
#endif

	STACK_VERIFY(stk);

	return STACK_NO_ERROR;
}

StackStatusCode DoStackPush(Stack_t* stk, Stack_elem_t value) {

	StackStatusCode status = STACK_NO_ERROR;

	STACK_VERIFY(stk);

	if (stk->size == stk->capacity) {
#ifdef CANARY_PROTECTION
		size_t size = (stk->capacity *= 2) * sizeof(Stack_elem_t) + 2 * sizeof(Canary_t);
		stk->data = (Stack_elem_t*)((char*)realloc((char*)stk->data - sizeof(Canary_t), size + (ALIGNMENT - size % ALIGNMENT)) + sizeof(Canary_t));

		*(Canary_t*)((char*)stk->data + stk->capacity * sizeof(Stack_elem_t)) = DATA_CANARY_HEX;
#else
		stk->data = (Stack_elem_t*)realloc(stk->data, (stk->capacity *= 2) * sizeof(Stack_elem_t));
#endif
		if (!stk->data)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);

		StackMemset(stk, stk->size, stk->capacity - stk->size, POISON);
	}

	STACK_VERIFY(stk);

	*(stk->data + stk->size++) = value;

	STACK_VERIFY(stk);

	return STACK_NO_ERROR;
}

StackStatusCode DoStackPop(Stack_t* stk, Stack_elem_t* value) {

	StackStatusCode status = STACK_NO_ERROR;

	STACK_VERIFY(stk);

	if ((4 * stk->size < stk->capacity && stk->size > DEFAULT_CAPACITY) || (stk->size <= DEFAULT_CAPACITY && stk->capacity > DEFAULT_CAPACITY)) {
#ifdef CANARY_PROTECTION
		size_t size = (stk->capacity = (stk->size < DEFAULT_CAPACITY ? DEFAULT_CAPACITY : stk->size)) * sizeof(Stack_elem_t) + 2 * sizeof(Canary_t);
		stk->data = (Stack_elem_t*)((char*)realloc((char*)stk->data - sizeof(Canary_t), size + (ALIGNMENT - size % ALIGNMENT)) + sizeof(Canary_t));

		*(Canary_t*)((char*)stk->data + stk->capacity * sizeof(Stack_elem_t)) = DATA_CANARY_HEX;
#else
		stk->data = (Stack_elem_t*)realloc(stk->data, (stk->capacity = stk->size) * sizeof(Stack_elem_t));
#endif
		if (!stk->data)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);
	}

	STACK_VERIFY(stk);

	if (stk->size == 0)
		STACK_ERROR_CHECK(STACK_POP_ERROR, stk);

	*value = *(stk->data + (--stk->size));
	*(stk->data + stk->size) = POISON;

	STACK_VERIFY(stk);

	return STACK_NO_ERROR;
}

StackStatusCode DoStackVerify(Stack_t* stk) {

	if (!stk)
		return STACK_POINTER_ERROR;

	if (!stk->capacity && !stk->size)
		return STACK_UNDERFLOW;

#ifdef CANARY_PROTECTION
	if (!CompareDouble(stk->canary1, STACK_CANARY_HEX))
		return STACK_LEFT_CANARY_ERROR;

	if (!CompareDouble(stk->canary2, STACK_CANARY_HEX))
		return STACK_RIGHT_CANARY_ERROR;

	if (!CompareDouble(*(Canary_t*)((char*)stk->data - sizeof(Canary_t)), DATA_CANARY_HEX))
		return DATA_LEFT_CANARY_ERROR;

	if (!CompareDouble(*(Canary_t*)((char*)stk->data + stk->capacity * sizeof(Stack_elem_t)), DATA_CANARY_HEX))
		return DATA_RIGHT_CANARY_ERROR;
#endif

	if (!stk->data)
		return STACK_DATA_POINTER_ERROR;

	if (stk->capacity < 0)
		return STACK_CAPACITY_ERROR;

	if (stk->size < 0)
		return STACK_SIZE_ERROR;

	if (stk->size > stk->capacity)
		return STACK_DIMENSIONS_ERROR;

	return STACK_NO_ERROR;
}

StackStatusCode DoStackDtor(Stack_t* stk) {

	if (!stk)
		STACK_ERROR_CHECK(STACK_POINTER_ERROR, stk);

#ifdef CANARY_PROTECTION
	stk->canary1 = TRASH;
	stk->canary2 = TRASH;
#endif

	stk->capacity = TRASH;
	stk->size 	  = TRASH;

	if (!stk->data)
		STACK_ERROR_CHECK(STACK_DATA_POINTER_ERROR, stk);

	char* alloc_memory = NULL;

#ifdef CANARY_PROTECTION
	alloc_memory = ((char*)stk->data - sizeof(Canary_t));
#else
	alloc_memory = (char*)stk->data;
#endif

	free(alloc_memory);
	alloc_memory = NULL;

#ifdef N_DEBUG
	printf("\n" GREEN("ALLOCATED MEMORY FREED!") "\n\n");
#endif

#ifdef HTML_DUMP
	StackStatusCode status = STACK_NO_ERROR;

	status = HtmlLogFinisher(stk);
	STACK_ERROR_CHECK(status, stk);
#endif

	return STACK_NO_ERROR;
}
