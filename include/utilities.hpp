#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

#include "../include/stack.hpp"

#define STACK_ERROR_CHECK(status, stk) {																	 		 	\
	if (status != STACK_NO_ERROR) {																						\
		fprintf(stderr, "\033[31;1mError (code %d): %s,\033[0m \033[33;4mFile: %s, Function: %s, Line: %d \n\033[0m",   \
				status, ErrorsMessenger(status), __FILE__, __PRETTY_FUNCTION__, __LINE__);								\
		if ((fclose(stderr)))																							\
			StackDtor(stk);																								\
		return status;																									\
	}																													\
}

#ifdef HTML_DUMP
#define DUMP(stk) {				 	 \
	status = StackDump(stk);	    \
	STACK_ERROR_CHECK(status, stk);	\
}
#else
#define DUMP(stk)
#endif

#define STACK_PUSH(stk, value) {		 \
	status = StackPush(stk, value);		\
	STACK_ERROR_CHECK(status, stk);		\
	DUMP(stk);							\
}

#define STACK_POP(stk, var_pointer) {												\
	status = StackPop(stk, var_pointer); 											\
	STACK_ERROR_CHECK(status, stk);													\
	printf("\033[33;6mStack element:\033[0m \033[34;6m%d\033[0m\n", *var_pointer);	\
	DUMP(stk);																		\
}

const char LOG_FILE_PATH[] = "html/log_eblan_main.html";
const size_t DEFAULT_CAPACITY = 16;
const size_t TRASH = 0xBEDADEDBEDA;

StackStatusCode HtmlLogStarter(Stack_t* stk);
StackStatusCode HtmlLogFinisher(Stack_t* stk);
StackStatusCode StackDump(Stack_t* stk);
StackStatusCode OpenLogFile(Stack_t* stk);

const char* ErrorsMessenger(StackStatusCode status);

size_t StrLen(const char* str);
StackStatusCode StrConcatenation(const char* string1, const char* string2, char** str_out, Stack_t* stk);

#endif //UTILITIES_INCLUDE
