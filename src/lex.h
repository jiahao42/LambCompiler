//LambLexer
//by James 2017/04/06

#ifndef LAMBLEXER_LEX_H_
#define LAMBLEXER_LEX_H_

#include "config.h"
#include "token.h"
#include "symbol_table.h"
#include "error.h"
#include "util.h"

class lexer {
private:
	std::string cur_line; 				/* Literally current line */
	line cur_line_info; 				/* Information of current line, including line number and line address, See symbol_table.h */
	c_token token; 						/* Represent the current token */
	bool is_comment; 					/* If current line is one of multi-line comment? */
public:
	lexer() { is_comment = false; }
	int lex_main(int argc, char** argv); 		/* Interface of the lexer */
	void lex(); 								/*  main function of lex  */
	void test_lexer();							/* test the lexer */
	void test_parser_aux();						/* prepare data for test parser */
	void dump_token_stream();					/* Output token stream to console */
	void read_file(); 							/* Read file and start to lex */
	void init_token(); 							/* Set the line number of token */
	void trim_space(size_t&); 					/* Trim the spaces */
	void parse_num_decimal(size_t&); 			/*  Parse decimal number */
	void parse_num_hex(size_t&);				/* Parse hexadecimal number */
	void parse_num_oct(size_t&);				/* Parse octal number */
	void parse_identifier(size_t&);				/* Parse identifier, start with letter or underscore */
	void parse_char(size_t&);					/* Parse character, start with ', also end with ', be careful with escape ' */
	void parse_string(size_t&);					/* Parse string, start with ", also end with ", be careful with escape " */
	void parse_single_line_comment(size_t&);	/*  Parse single line commeng, start with // */
	void parse_multi_line_comment(size_t&);		/* Parse multi-line comment, start with *\/, also end with *\/ */ 
};

void init_symbol_table(const char* filedir, const char* filename); /* Initialize the symbol table */

#endif /* end of LAMBLEXER_LEX_H_ */