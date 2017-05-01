#include "parser_config.h"
#include "parse.h"

extern source source_file;


c_token& parser::get_next_token() {
	return source_file.c_token_vector[token_idx++];
}

inline bool parser::get_token_precedence() {
	c_ttype prev = source_file.c_token_vector[token_idx - 2].get_type();
	//TODO
}

