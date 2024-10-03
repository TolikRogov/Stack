#include "../include/utilities.hpp"

//TODO:
//	-I) -I key (я пытался)
//	-II) Html file with different dumps: 1) memory (calloc, realloc), 2) stack ctor, 3) stack push, 4) stack pop,
//									  5) stack dtor, 6) stack verify, 7) Stack status code
//	I) HexSpeak
//	II) PROTECTION -> 1) Canary protection + 2) Hash protection
//	II) DUMP from DED with colors
//	III) Bit move in errors
//	IV)	STACK UNDERFLOW conception
//	V) Canaries for LOG and STACK INFO

int main() {

	StackStatusCode status = STACK_NO_ERROR;

	INIT_STACK(stk);

	STACK_CTOR(&stk, 1);

	*(Canary_t*)((char*)stk.data + stk.capacity * sizeof(Stack_elem_t)) = 0;

	for (Stack_elem_t i = 0; i < 20; i++)
		STACK_PUSH(&stk, i);

	Stack_elem_t x = 0;
	for (Stack_elem_t i = 0; i < 20; i++)
		STACK_POP(&stk, &x);

	STACK_DTOR(&stk);

	return 0;
}
