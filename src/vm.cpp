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

void eval();
void entry();

int main() {
	text = new int[stack_size];
	old_text = new int[stack_size];
	stack = new int[stack_size];
	data = new char[stack_size];
	
	ebx = stack;
	esp = stack;
	
	size_t i = 0;
	text[i++] = LOADA; // LOADA 10
	text[i++] = 10;
	text[i++] = LOADB;
	text[i++] = 20;
	text[i++] = ADD;
	text[i++] = HALT;
	
	entry();
}

void entry() {
	eval();
}

void eval() {
	int op, *tmp;
	while (1) {
		eip++;
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
			case HALT:
				std::cout << "Result: " << *eax << std::endl;
			default:
				std::cout << "Wrong op!" << std::endl;
		}
	}
}












