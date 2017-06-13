#ifndef LAMB_COMPILER_VM_H_
#define LAMB_COMPILER_VM_H_

#include <iostream>

enum {
	ADD, SUB, MUL, DIV, 
	PUSH, POP, 
	JMP, 
	MOV, LEA, 
	LOADA, // move the next number to eax
	LOADB, // move the next number to ebx
	HALT, 
};




#endif /* end of LAMB_COMPILER_VM_H_ */