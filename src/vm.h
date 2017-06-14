#ifndef LAMB_COMPILER_VM_H_
#define LAMB_COMPILER_VM_H_

#include <iostream>
#include <unordered_map>

extern std::vector<std::string> code;
extern std::vector<std::string> stack_data;

enum assm_op{
	ADD, SUB, MUL, DIV, 
	PUSH, POP, 
	JMP, 
	MOV, LEA, 
	LOADA, // move the next number to eax
	LOADB, // move the next number to ebx
	HALT, 
};

static std::unordered_map<std::string, enum assm_op> op_table = {
	{"ADD", ADD},
	{"HALT", HALT},
};

class vm {
private:
	int *text,            // text segment
		*old_text,        // for dump text segment
		*stack;           // stack
		
	char *data;           // data segment
	const static int stack_size = 1024;

	int *eip,			// registers
		*eax,
		*ebx,
		*ecx,
		*edx,
		*ebp,
		*esp;
public:
	void test() {
		size_t i = 0;
		text[i++] = LOADA; // LOADA 10
		text[i++] = LOADB;
		text[i++] = ADD;
		text[i++] = HALT;
		*esp++ = 10;
		*esp++ = 20;
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
		eip = text;
	}
	void entry() {
		eval();
	}
	void eval() {
		int op;
		while (1) {
			op = *eip;
			std::cout << "current op: " << op << std::endl;
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
					*eax = *--esp;
					break;
				case LOADB:
					*ebx = *--esp;
					break;
				default:
					std::cout << "Wrong op!" << std::endl;
			}
			eip++;
		}
	}
	void execute_code() {
		code.push_back("HALT");
		init();
		transform_code();
		entry();
	}
	void transform_code() {
		size_t i = 0;
		for (std::string s : code) {
			auto it = op_table.find(s);
			if (it == op_table.end()) {
				text[i++] = stoi(s);
				std::cout << "transforming: " << stoi(s) << std::endl;
			} else {
				text[i++] = it -> second;
				std::cout << "transforming: " << s << std::endl;
			}
		}
		for (std::string s : stack_data) {
			*esp++ = stoi(s);
		}
	}
	void vm_main() {
		init();
		test();
		entry();
	}
};


#endif /* end of LAMB_COMPILER_VM_H_ */