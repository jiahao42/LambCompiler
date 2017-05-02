#include "parser_config.h"
#include "parse.h"

extern source source_file;


c_token& parser::get_next_token() {
	cur_token = source_file.c_token_vector[token_idx++];
}

expr_node* parse::parse_expr();
expr_node* parse::parse_identifier_node() {
	std::string name = cur_token.get_name();
	get_next_token();
	if (cur_token.get_type() != C_OPEN_PAREN)
		return new var_expr_node(name);
	get_next_token();
	std::vector<expr_node*> args;
	if (cur_token.get_type() != C_CLOSE_PAREN) {
		while (1) {
			expr_node* arg = parse_expr();
			if (!arg) return 0;
			arg.push_back(arg);
			
			if (cur_token.get_type() == C_OPEN_PAREN)
				break;
			
			if (cur_token.get_type() != C_COMMA)
				
		}
	}
}

expr_node* parse::parse_number_node();
expr_node* parse::parse_paren_node();
expr_node* parse::parse_primary();
expr_node* parse::parse_bin_op_rhs(); //TODO
expr_node* parse::parse_expr();
prototype_node* parser::parse_prototype();
function_node*  parser::parse_definition();
function_node*  parser::parse_top_level_expr();
