#ifndef LOG_UTILITIES_INCLUDE
#define LOG_UTILITIES_INCLUDE

#include "libraries.hpp"

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

#endif //LOG_UTILITIES_INCLUDE
