//LambCompiler
//by James 2017/05/01
#ifndef LAMB_COMPILER_PARSER_H_
#define LAMB_COMPILER_PARSER_H_

#include "lex.h"
#include "AST.h"

class parser {
private:
	int token_idx;
	c_token cur_token;
	c_token dummy;
public:
	parser() : token_idx(0), dummy(0, 0, C_EQ, "") {}
	void parse_main();
	c_token& get_next_token();
	expr_node* parse_identifier_node();
	expr_node* parse_number_node();
	expr_node* parse_paren_node();
	expr_node* parse_primary();
	expr_node* parse_bin_op_rhs(c_ttype prev_type, expr_node* lhs);
	expr_node* parse_expr();
	prototype_node* parse_prototype();
	function_node* parse_definition();
	function_node* parse_top_level_expr();
	void handle_definition();
	void handle_top_level_expr();
	void main_loop();
};


#endif