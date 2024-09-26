#include "../include/utilities.hpp"

//TODO:
//	1) StackVerify
//	2) Html file with memory
//	3) DUMP: function that return dump information

int main() {

	StackStatusCode status = STACK_NO_ERROR;

	Stack_t stk = {};

	status = StackCtor(&stk);
	STACK_ERROR_CHECK(status, &stk);

#ifdef HTML_DUMP
	status = HtmlLogStarter(&stk);
	STACK_ERROR_CHECK(status, &stk);
#endif

	for (Stack_elem_t i = 0; i < 1000; i++)
		STACK_PUSH(&stk, i);

	Stack_elem_t x = 0;
	STACK_POP(&stk, &x);
	STACK_POP(&stk, &x);

#ifdef HTML_DUMP
	status = HtmlLogFinisher(&stk);
	STACK_ERROR_CHECK(status, &stk);
#endif

	status = StackDtor(&stk);
	STACK_ERROR_CHECK(status, &stk);

	return 0;
}
