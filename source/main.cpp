#include "../include/utilities.hpp"

int main() {

	StackStatusCode status = STACK_NO_ERROR;

	Stack_t stk = {};

	status = StackCtor(&stk);
	STACK_ERROR_CHECK(status, &stk);

#ifdef HTML_DUMP
	status = HtmlLogStarter(&stk);
	STACK_ERROR_CHECK(status, &stk);
#endif

	status = StackPush(&stk, 10);
	STACK_ERROR_CHECK(status, &stk);

	DUMP(&stk);

#ifdef HTML_DUMP
	status = HtmlLogFinisher(&stk);
	STACK_ERROR_CHECK(status, &stk);
#endif

	status = StackDtor(&stk);
	STACK_ERROR_CHECK(status, &stk);

	return 0;
}
