//LambCompiler
//by James 2017/05/01

#include "lex.h"
#include "AST.h"

class parser {
private:
	int token_idx;
	c_token cur_token;
	
public:
	parse() : token_idx(0) {}
	parse_main();
	c_token& get_next_token();
	inline bool get_token_precedence();
	expr_node* parse_identifier_node();
	expr_node* parse_number_node();
	expr_node* parse_paren_node();
	expr_node* parse_primary();
	expr_node* parse_bin_op_rhs(); //TODO
	expr_node* parse_expr();
	prototype_node* parse_prototype();
	function_node* parse_definition();
	function_node* parse_top_level_expr();
	
}