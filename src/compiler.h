//LambCompiler
//by James 2017/05/02
#ifndef LAMB_COMPILER_H_
#define LAMB_COMPILER_H_

#include "lex.h"
#include "parser.h"
#include "vm.h"

class compiler {
private:
	lexer l;
	parser p;
	vm v;
public:
	int compile(int argc, char** argv);
	void test_parser();
};

#endif