#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

#include "../include/stack.hpp"

#define RED(str) 		"\033[31;1m" str "\033[0m"
#define YELLOW(str) 	"\033[33;4m" str "\033[0m"
#define GREEN(str) 		"\033[32;6m" str "\033[0m"

#define STACK_ERROR_CHECK(status, stk) {																	 		 	\
	if (status != STACK_NO_ERROR) {																						\
		fprintf(stderr, RED("Error (code %d): %s, ") YELLOW("File: %s, Function: %s, Line: %d\n"),   					\
				status, StackErrorsMessenger(status), __FILE__, __PRETTY_FUNCTION__, __LINE__);							\
		if (!(fclose(stderr)))																							\
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

#define STACK_POP(stk, var_pointer) {			\
	status = StackPop(stk, var_pointer); 		\
	STACK_ERROR_CHECK(status, stk);				\
	DUMP(stk);									\
}

const size_t DEFAULT_CAPACITY = 16;
const size_t TRASH = 0xBEDADEDBEDA;

struct HtmlFile {
	const char* file_name;
	char* file_path;
};

enum HtmlFiles {
	MAIN
};

StackStatusCode HtmlLogStarter(Stack_t* stk);
StackStatusCode HtmlLogFinisher(Stack_t* stk);
StackStatusCode StackDump(Stack_t* stk);

StackStatusCode RunMainHtmlFile(Stack_t* stk);
StackStatusCode MakeHtmlFolder(Stack_t* stk);
StackStatusCode MakeHtmlFilePath(Stack_t* stk);

const char* StackErrorsMessenger(StackStatusCode status);

size_t StrLen(const char* str);
StackStatusCode StrConcatenation(const char* string1, const char* string2, char** str_out, Stack_t* stk);

#endif //UTILITIES_INCLUDE
