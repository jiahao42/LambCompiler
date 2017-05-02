//LambLexer
//by James 2017/04/06

#include "lex_config.h"
#include "compiler.h"

int main(int argc, char** argv) {
	//lexer l;
	//return l.lex_main(argc, argv);
	compiler c;
	return c.compile(argc, argv);
}



