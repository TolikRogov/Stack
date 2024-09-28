#include "../include/utilities.hpp"

const char* folders[] = { "html_log_eblan/",
						  "styles_log_eblan/" };

size_t cnt_of_files_in_log_parts[] = { (size_t)HP_END,  (size_t)SP_END };

const char* files_in_log_parts[] = { "main.html",
									"table.html",
		    						"styles.css" };

StackStatusCode DoStackCtor(Stack_t* stk, size_t capacity) {

#ifdef HTML_DUMP
	StackStatusCode status = STACK_NO_ERROR;

	status = FilesCtor(stk);
	STACK_ERROR_CHECK(status, stk);

	status = HtmlMainLogStarter(stk);
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

StackStatusCode FilesCtor(Stack_t* stk) {

	stk->log_parts = (Log_Parts*)calloc(LP_END, sizeof(Log_Parts));
	if (!stk->log_parts)
		STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);

	size_t pref_sum_cnt[(int)LP_END + 1] = {};
	pref_sum_cnt[1] = cnt_of_files_in_log_parts[0];
	for (size_t i = 2; i < LP_END + 1; i++)
		pref_sum_cnt[i] = pref_sum_cnt[i - 1] + cnt_of_files_in_log_parts[i - 1];

	for (size_t i = 0; i < LP_END; i++) {
		stk->log_parts[i].folder = folders[i];
		stk->log_parts[i].files_size = cnt_of_files_in_log_parts[i];

		stk->log_parts[i].files = (File*)calloc(cnt_of_files_in_log_parts[i], sizeof(File));
		if (!stk->log_parts[i].files)
			STACK_ERROR_CHECK(STACK_ALLOC_ERROR, stk);

		for (size_t j = 0; j < cnt_of_files_in_log_parts[i]; j++)
			stk->log_parts[i].files[j] = { .file_name = files_in_log_parts[pref_sum_cnt[i] + j] };
	}

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
	status = HtmlMainLogFinisher(stk);
	STACK_ERROR_CHECK(status, stk);

	FilesDtor(stk);
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

StackStatusCode FilesDtor(Stack_t* stk) {

	for (size_t i = 0; i < LP_END; i++) {

		for (size_t j = 0; j < cnt_of_files_in_log_parts[i]; j++) {
			if (stk->log_parts[i].files[j].file_path) {
				free(stk->log_parts[i].files[j].file_path);
				stk->log_parts[i].files[j].file_path = NULL;
			}
		}
	}

	return STACK_NO_ERROR;
}
