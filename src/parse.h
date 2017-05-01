//LambCompiler
//by James 2017/05/01

#include "lex.h"

extern source source_file;
static int token_idx = 0;
static c_token cur_token;

c_token& get_next_token() {
	return source_file.c_token_vector[token_idx++];
}

inline bool get_token_precedence() {
	c_ttype prev = source_file.c_token_vector[token_idx - 2].get_type();
	//TODO
}