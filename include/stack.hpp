#ifndef STACK_INCLUDE
#define STACK_INCLUDE

typedef double Stack_elem_t;

#ifdef CANARY_PROTECTION
	typedef double Canary_t;
#endif

#ifdef HASH_PROTECTION
	typedef size_t Hash_t;
#endif

enum StackStatusCode {
	STACK_NO_ERROR,
	STACK_ERROR,

	STACK_ALLOC_ERROR,

	STACK_FILE_OPEN_ERROR,
	STACK_FILE_CLOSE_ERROR,
	STACK_DIR_OPEN_ERROR,
	STACK_DIR_CLOSE_ERROR,

	STACK_DIR_DELETE_ERROR,
	STACK_DIR_MAKE_ERROR,
	STACK_RUN_HTML_ERROR,

	STACK_POINTER_ERROR,
	STACK_DATA_POINTER_ERROR,

	STACK_UNDERFLOW,
	STACK_SIZE_ERROR,
	STACK_CAPACITY_ERROR,
	STACK_DIMENSIONS_ERROR,

	STACK_POP_ERROR,

	STACK_LEFT_CANARY_ERROR,
	STACK_RIGHT_CANARY_ERROR,

	STACK_DATA_LEFT_CANARY_ERROR,
	STACK_DATA_RIGHT_CANARY_ERROR,

	STACK_HASH_ERROR
};

struct StackLogInfo {
	const char* stack_name;
	const char* file_name;
	const size_t line;
};

struct Stack_t {

#ifdef HASH_PROTECTION
	Hash_t hash;
#endif

#ifdef CANARY_PROTECTION
	Canary_t canary1;
#endif

	int status;

#ifdef HTML_DUMP
	StackLogInfo stack_info;
#endif

#ifdef HASH_PROTECTION
	Hash_t data_hash;
#endif

	Stack_elem_t* data;
	size_t size;
	size_t capacity;

	Dir log;

#ifdef CANARY_PROTECTION
	Canary_t canary2;
#endif
};

StackStatusCode DoStackCtor(Stack_t* stk, size_t capacity);
StackStatusCode DoStackVerify(Stack_t* stk);
StackStatusCode DoStackPush(Stack_t* stk, Stack_elem_t value);
StackStatusCode DoStackPop(Stack_t* stk, Stack_elem_t* value);
StackStatusCode DoStackDtor(Stack_t* stk);

StackStatusCode CheckerStackStatus(Stack_t* stk, const char* file, const char* func, const size_t line);

#ifdef HASH_PROTECTION
	Hash_t DJB2Hash(const void* array, const size_t size_in_bytes);
#endif

#endif //STACK_INCLUDE
