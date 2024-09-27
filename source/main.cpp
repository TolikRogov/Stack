#include "../include/utilities.hpp"

//TODO:
//	I) Html file with different dumps: 1) memory (calloc, realloc), 2) stack ctor, 3) stack push, 4) stack pop,
//									  5) stack dtor, 6) stack verify, 7) Stack status code
//	II) -I key (я пытался)
//	III) STACK_RETURN -> Stack Verify -> Stack Dump
//	IV) HexSpeak
//	V) PROTECTION -> 1) Canary protection + 2) Hash protection
//	VI) DUMP from DED (with conditional compilation in stack prototype)

int main() {

	StackStatusCode status = STACK_NO_ERROR;

	Stack_t stk = {};

	status = StackCtor(&stk, 10);
	STACK_ERROR_CHECK(status, &stk);

#ifdef HTML_DUMP
	status = HtmlLogStarter(&stk);
	STACK_ERROR_CHECK(status, &stk);
#endif

	for (Stack_elem_t i = 0; i < 1000; i++)
		STACK_PUSH(&stk, i);

	Stack_elem_t x = 0;
	STACK_POP(&stk, &x);

#ifdef HTML_DUMP
	status = HtmlLogFinisher(&stk);
	STACK_ERROR_CHECK(status, &stk);
#endif

	status = StackDtor(&stk);
	STACK_ERROR_CHECK(status, &stk);

	return 0;
}
