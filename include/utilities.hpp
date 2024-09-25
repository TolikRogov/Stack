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
#endif

const char LOG_FILE_PATH[] = "log_eblan.html";
const size_t DEFAULT_CAPACITY = 16;

StackStatusCode HtmlLogStarter(Stack_t* stk);
StackStatusCode HtmlLogFinisher(Stack_t* stk);
StackStatusCode StackDump(Stack_t* stk);
const char* ErrorsMessenger(StackStatusCode status);

#endif //UTILITIES_INCLUDE
