#ifndef LAMB_COMPILER_H_
#define LAMB_COMPILER_H_

#include "lex.h"
#include "parser.h"

class compiler {
private:
	lexer l;
	parser p;
public:
	int compile(int argc, char** argv);
};

#endif