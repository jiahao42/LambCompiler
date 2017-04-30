//LambLexer
//by James 2017/04/06

#include "lex_config.h"
#include "lex.h"

int main(int argc, char** argv) {
	lexer l(argc, argv);
	return l.lex_main(argc, argv);
}



