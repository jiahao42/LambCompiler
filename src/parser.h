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
	std::map<c_ttype, int> bin_op_precedence;
public:
	parser() : token_idx(0), dummy(0, 0, C_EQ, "") {
		bin_op_precedence[C_EQ] = 5; 		/*  =  */
		bin_op_precedence[C_EQ_EQ] = 15;	/*  == */
		bin_op_precedence[C_LESS] = 20;		/*  <  */
	    bin_op_precedence[C_PLUS] = 35;		/*  +  */
		bin_op_precedence[C_MINUS] = 35;	/*  -  */
		bin_op_precedence[C_MULT] = 40;		/*  *  */
		bin_op_precedence[C_DIV] = 40;		/*  /  */
	}
	void parse_main();
	inline c_ttype& get_next_token();
	int get_op_precedence();
	
	void handle_top_level_expr();
	function_node* parse_top_level_expr();
	expr_node* parse_identifier_node();
	expr_node* parse_number_node();
	expr_node* parse_paren_node();
	expr_node* parse_primary();
	expr_node* parse_bin_op_rhs(int prev_type, expr_node* lhs);
	expr_node* parse_expr();
	
	void handle_if_statement();
	expr_node* parse_if_statement();
	
	void handle_for_loop_expr();
	expr_node* parse_for_loop_expr();
	
	void handle_while_expr();
	expr_node* parse_while_expr();
	
	//prototype_node* parse_prototype();
	//function_node* parse_definition();	
	//void handle_definition();
	
	expr_node* Error(std::string str);
	prototype_node* ErrorP(std::string str);
	function_node* ErrorF(std::string str);
};


#endif