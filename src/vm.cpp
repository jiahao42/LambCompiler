#include "vm.h"

int *text,            // text segment
    *old_text,        // for dump text segment
    *stack;           // stack
	
char *data;           // data segment
const int stack_size = 1024;

int *eip,
	*eax,
	*ebx,
	*ecx,
	*edx,
	*ebp,
	*esp;

void init();
void test();
void eval();
void entry();

int main() {
	init();
	test();
	entry();
}

void test() {
	size_t i = 0;
	eip = text;
	text[i++] = LOADA; // LOADA 10
	text[i++] = 10;
	text[i++] = LOADB;
	text[i++] = 20;
	text[i++] = ADD;
	text[i++] = HALT;
}
void init() {
	text = new int[stack_size];
	old_text = new int[stack_size];
	stack = new int[stack_size];
	data = new char[stack_size];
	
	eax = new int();
	ebx = new int();
	ebx = new int();
	edx = new int();
	
	ebx = stack;
	esp = stack;
}
void entry() {
	eval();
}

void eval() {
	int op, *tmp;
	while (1) {
		op = *eip;
		//std::cout << "current op: " << op << std::endl;
		if (op == HALT) {
			std::cout << "Result: " << *eax << std::endl;
			break;
		}
		switch (op) {
			case ADD:
				*eax = *eax + *ebx;
				break;
			case SUB:
				*eax = *eax - *ebx;
				break;
			case LOADA:
				eip++;
				*eax = *eip;
				break;
			case LOADB:
				eip++;
				*ebx = *eip;
				break;
			default:
				std::cout << "Wrong op!" << std::endl;
		}
		eip++;
	}
}












