#ifndef LAMB_COMPILER_VM_H_
#define LAMB_COMPILER_VM_H_

#include <iostream>
#include <unordered_map>

extern std::vector<std::string> code;
extern std::vector<std::string> stack_data;

enum assm_op {
    ADD,
    SUB,
    MUL,
    DIV, // 0-3
    PUSH,
    POP, // 4-5
    JMP, // 6
    MOV,
    LEA,   // 7-8
    LOADA, // 9 - move the next number to eax
    LOADB, // 10 - move the next number to ebx
    HALT,  // 11
};

static std::unordered_map<std::string, enum assm_op> op_table = {
    {"ADD", ADD}, {"HALT", HALT}, {"LOADA", LOADA}, {"LOADB", LOADB},
};

class vm {
private:
    int *text,     // text segment
        *old_text, // for dump text segment
        *stack;    // stack

    char *data; // data segment
    const static int stack_size = 1024;

    int *eip, // registers
        *eax, *ebx, *ecx, *edx, *ebp, *esp;

public:
    void test() {
        size_t i = 0;
        text[i++] = LOADA; // LOAD 20 to eax
        text[i++] = LOADB; // LOAD 10 to ebx
        text[i++] = ADD;   // ADD eax and ebx
        text[i++] = HALT;  // HALT
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
    void entry() { eval(); }
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
    void vm_main() {
        init();
        test();
        entry();
    }
};

#endif /* end of LAMB_COMPILER_VM_H_ */