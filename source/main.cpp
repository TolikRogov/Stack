#include "../include/STACK_LIBRARY.hpp"

//TODO:
//	~)		TheROBT: color printf, error check, html log
//  ~) 		-I key (я пытался)

//  IV)     Possible errors: not check memset return value, stack ctor -1, with second stack

int main() {

	INIT_STACK(stk);

	STACK_CTOR(&stk, 1);

	for (Stack_elem_t i = 0; i < 20; i++)
		STACK_PUSH(&stk, i);

	Stack_elem_t x = 0;
	for (Stack_elem_t i = 0; i < 20; i++)
		STACK_POP(&stk, &x);

	STACK_DTOR(&stk);

	return 0;
}
