#include "../include/utilities.hpp"

//TODO:
//	-I) -I key (я пытался)
//	I) 		PROTECTION -> 1) Canary protection + 2) Hash protection
//	II) 	DUMP from DED with colors
//	III) 	STACK UNDERFLOW conception
//	IV) 	Possible errors: not check memset return value,
//	V)	 	MORE FILES: utilities for stack optional things, log for html dump
//	VI)		Different enums for log errors and stack errors

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
