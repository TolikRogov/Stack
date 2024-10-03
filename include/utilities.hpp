#ifndef UTILITIES_INCLUDE
#define UTILITIES_INCLUDE

#include "../include/config.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

struct File {
	const char* file_name;
	char* file_path;
};

struct Dir {
	const char* dir_name = "log_eblan/";

	size_t cnt_files = 2;
	File files[2] = { {.file_name = "main.html"},
					 {.file_name = "table.html"} };

	size_t cnt_dirs = 1;
	struct ChildDir {
		const char* c_dir_name = "css/";
		char* c_dir_path;

		size_t c_dir_cnt_files = 1;
		File files[1] = { { .file_name = "style.css" } };
	} styles;
};

#include "../include/stack.hpp"

#define RED(str) 		"\033[31;1m" str "\033[0m"
#define YELLOW(str) 	"\033[33;4m" str "\033[0m"
#define GREEN(str) 		"\033[32;6m" str "\033[0m"

#ifdef HTML_DUMP
#define INIT_STACK(stk) Stack_t stk = { .stack_info = {#stk, __FILE__, __LINE__}}
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
#define DUMP(stk, func_name) {				 	  		 										 \
	status = DoStackDumpMain(stk, {.file = __FILE__, .line = __LINE__, .func = func_name});	 	 \
	STACK_ERROR_CHECK(status, stk);																\
	status = DoStackDumpTable(stk);																\
	STACK_ERROR_CHECK(status, stk);																\
}
#else
#define DUMP(stk, func)
#endif

#define STACK_CTOR(stk, capacity) {					 \
	if (capacity < 0)								\
		STACK_ERROR_CHECK(STACK_SIZE_ERROR, stk);	\
	status = DoStackCtor(stk, capacity);			\
	STACK_ERROR_CHECK(status, stk);					\
	DUMP(stk, "STACK_CTOR");						\
}

#define STACK_PUSH(stk, value) {		 	 \
	status = DoStackPush(stk, value);		\
	STACK_ERROR_CHECK(status, stk);			\
	DUMP(stk, "STACK_PUSH");				\
}

#define STACK_POP(stk, var_pointer) {		 \
	status = DoStackPop(stk, var_pointer); 	\
	STACK_ERROR_CHECK(status, stk);			\
	DUMP(stk, "STACK_POP");					\
}

#define STACK_VERIFY(stk) {					 \
	status = DoStackVerify(stk);			\
	STACK_ERROR_CHECK(status, stk);			\
}

#define STACK_DTOR(stk) {					 \
	status = DoStackDtor(stk);				\
	STACK_ERROR_CHECK(status, stk);			\
}

const size_t 		DEFAULT_CAPACITY 	= 16;
const size_t 		TRASH 			  	= 0xBEDADEDBEDA;
const Stack_elem_t 	POISON 	  			= -6e-99;
const double 		EPS 			 	= 1e-10;
const double 		STACK_CANARY_HEX	= 0xDEADDED;
const double		DATA_CANARY_HEX		= 0xBADFACE;
const size_t 		ALIGNMENT	 		= 8;

enum HTML {
	MAIN,
	TABLE
};

enum STYLES {
	CSS
};

struct DumpInfo {
	const char* file;
	const size_t line;
	const char* func;
};

StackStatusCode DirCtor(Stack_t* stk);

StackStatusCode MakeDirsPaths(Stack_t* stk);
StackStatusCode MakeFilesPaths(Stack_t* stk);
StackStatusCode MakeDirsFolders(Stack_t* stk);
StackStatusCode DeleteLogDir(Stack_t* stk);

StackStatusCode HtmlLogStarter(Stack_t* stk);
StackStatusCode CssLogStarter(Stack_t* stk);

StackStatusCode HtmlTableLog(Stack_t* stk);
StackStatusCode HtmlTableLogFinisher(Stack_t* stk);

StackStatusCode DoStackDumpMain(Stack_t* stk, DumpInfo dump_info);
StackStatusCode DoStackDumpTable(Stack_t* stk);

StackStatusCode HtmlLogFinisher(Stack_t* stk);
StackStatusCode RunMainHtmlFile(Stack_t* stk);

const char* StackErrorsMessenger(StackStatusCode status);

size_t StrLen(const char* str);
StackStatusCode StrConcatenation(const char* string1, const char* string2, char** str_out, Stack_t* stk);
StackStatusCode StackMemset(Stack_t* stk, const size_t start, const size_t cnt, const Stack_elem_t value);
int CompareDouble(const double var1, const double var2);

#endif //UTILITIES_INCLUDE
