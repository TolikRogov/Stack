#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

struct File {
	const char* file_name;
	char* file_path;
};

struct Log_Parts {
	const char* folder;
	unsigned long files_size;
	File* files;
};

#include "../include/stack.hpp"

#define RED(str) 		"\033[31;1m" str "\033[0m"
#define YELLOW(str) 	"\033[33;4m" str "\033[0m"
#define GREEN(str) 		"\033[32;6m" str "\033[0m"

#ifdef HTML_DUMP
#define INIT_STACK(stk) Stack_t stk = { #stk, __FILE__, __LINE__ }
#else
#define INIT_STACK(stk) Stack_t stk = {}
#endif

#define STACK_ERROR_CHECK(status, stk) {																	 	 		 \
	if (status != STACK_NO_ERROR) {																						\
		fprintf(stderr, RED("Error (code %d): %s, ") YELLOW("File: %s, Function: %s, Line: %d\n"),   					\
				status, StackErrorsMessenger(status), __FILE__, __PRETTY_FUNCTION__, __LINE__);							\
		if (!(fclose(stderr)))																							\
			DoStackDtor(stk);																							\
		return status;																									\
	}																													\
}

#ifdef HTML_DUMP
#define DUMP(stk) {				 	  		 \
	status = DoStackDump(stk);	    		\
	STACK_ERROR_CHECK(status, stk);			\
}
#else
#define DUMP(stk)
#endif

#define STACK_CTOR(stk, capacity) {			 \
	status = DoStackCtor(stk, capacity);	\
	STACK_ERROR_CHECK(status, stk);			\
	DUMP(stk);								\
}

#define STACK_PUSH(stk, value) {		 	 \
	status = DoStackPush(stk, value);		\
	STACK_ERROR_CHECK(status, stk);			\
	DUMP(stk);								\
}

#define STACK_POP(stk, var_pointer) {		 \
	status = DoStackPop(stk, var_pointer); 	\
	STACK_ERROR_CHECK(status, stk);			\
	DUMP(stk);								\
}

#define STACK_VERIFY(stk) {					 \
	status = DoStackVerify(stk);			\
	STACK_ERROR_CHECK(status, stk);			\
}

#define STACK_DTOR(stk) {					 \
	status = DoStackDtor(stk);				\
	STACK_ERROR_CHECK(status, stk);			\
}

const size_t DEFAULT_CAPACITY = 16;
const size_t TRASH = 0xBEDADEDBEDA;

enum LOG_PARTS {
	HTML,
	STYLE,
	LP_END
};

enum HTML_PARTS {
	MAIN,
	TABLE,
	HP_END
};

enum STYLE_PARTS {
	CSS,
	SP_END
};

StackStatusCode CssLogStarter(Stack_t* stk);
StackStatusCode HtmlMainLogStarter(Stack_t* stk);
StackStatusCode HtmlMainLogFinisher(Stack_t* stk);

StackStatusCode DoStackDump(Stack_t* stk);

StackStatusCode RunMainHtmlFile(Stack_t* stk);

StackStatusCode MakeLpFolders(Stack_t* stk);
StackStatusCode MakeFilesPath(Stack_t* stk);

const char* StackErrorsMessenger(StackStatusCode status);

size_t StrLen(const char* str);
StackStatusCode StrConcatenation(const char* string1, const char* string2, char** str_out, Stack_t* stk);

#endif //UTILITIES_INCLUDE
