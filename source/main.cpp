#include "../include/utilities.hpp"

//TODO:
//	1) DUMP number in one table
//	2) StackPop
//	3) StackVerify

int main() {

	StackStatusCode status = STACK_NO_ERROR;

	Stack_t stk = {};

	status = StackCtor(&stk);
	STACK_ERROR_CHECK(status, &stk);

#ifdef HTML_DUMP
	status = HtmlLogStarter(&stk);
	STACK_ERROR_CHECK(status, &stk);
#endif

	STACK_PUSH(&stk, 10);

	DUMP(&stk);

	STACK_PUSH(&stk, 20);

	DUMP(&stk);

#ifdef HTML_DUMP
	status = HtmlLogFinisher(&stk);
	STACK_ERROR_CHECK(status, &stk);
#endif

	status = StackDtor(&stk);
	STACK_ERROR_CHECK(status, &stk);

	return 0;
}
