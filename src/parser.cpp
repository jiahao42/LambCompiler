//LambCompiler
//by James 2017/05/02
#include "config.h"
#include "parser.h"

#define CUR_TOKEN_TYPE cur_token.get_type()
#define CUR_TOKEN_NAME cur_token.get_name()
#define CUR_TOKEN_LINE cur_token.get_line()
#define CUR_TOKEN_COL  cur_token.get_col()
#define CUR_LINE	   source_file.get_line_content(CUR_TOKEN_LINE)
extern source source_file;

expr_node* parser::Error(std::string str) {
	std::cout << source_file.filename << ":" << CUR_TOKEN_LINE << ":" << CUR_TOKEN_COL << " : " <<"Error: " << str << std::endl;
	std::cout << CUR_LINE << std::endl;
	std::cout << std::setw(CUR_TOKEN_COL + 1);
	for (size_t i = 0; i < CUR_TOKEN_NAME.size(); i++)
		std::cout << "^";
	std::cout << std::endl;
	return 0;
}
prototype_node* parser::ErrorP(std::string str) { Error(str); return 0; }
function_node* parser::ErrorF(std::string str) { Error(str); return 0; }

int parser::get_op_precedence() {
  // Make sure it's a declared binop.
  int token_prec = bin_op_precedence[CUR_TOKEN_TYPE];
  if (token_prec <= 0) return -1;
  return token_prec;
}

inline c_ttype& parser::get_next_token() {
	if (static_cast<size_t>(token_idx) < source_file.c_token_vector.size())
		cur_token = source_file.c_token_vector[token_idx++];
	else
		cur_token.set_type(C_EOF);
	PRINT_TOKEN(CUR_TOKEN_NAME);
	return CUR_TOKEN_TYPE;
}

expr_node* parser::parse_identifier_node() {
	PRINT("parse_identifier_node");
	std::string name = CUR_TOKEN_NAME;
	get_next_token(); // skip identifier
	if (CUR_TOKEN_TYPE != C_OPEN_PAREN)
		return new var_expr_node(name);

	// Make sure it is a function call
	get_next_token(); // skip '('
	std::vector<expr_node*> args;
	if (CUR_TOKEN_TYPE != C_CLOSE_PAREN) {
		while (1) {
			expr_node* arg = parse_expr();
			if (!arg) return 0;
			args.push_back(arg);

			if (CUR_TOKEN_TYPE == C_CLOSE_PAREN) // argument list finish ?
				break;

			if (CUR_TOKEN_TYPE != C_COMMA) // more arguments ?
				return Error("Expected ')' or ',' in argument list");
			get_next_token(); // skip ','
		}
	}

	get_next_token(); // skip ')'

	return new call_expr_node(name, args);
}

expr_node* parser::parse_number_node() {
	PRINT("parse_number_node");
	double val = stod(CUR_TOKEN_NAME);
	expr_node* res = new number_expr_node(val);
	get_next_token();
	return res;
}

expr_node* parser::parse_paren_node() {
	PRINT("parse_paren_node");
	get_next_token(); //skip '('
	expr_node* node = parse_expr();
	if (!node) return 0;

	if (CUR_TOKEN_TYPE != C_CLOSE_PAREN)
		return Error("expected ')'");
	get_next_token();
	return node;
}

expr_node* parser::parse_primary() {
	PRINT("parse_primary");
	c_ttype cur_type = CUR_TOKEN_TYPE;
	switch (cur_type) {
		default: return Error("unknown token when expecting an expression");
		case C_NAME: return parse_identifier_node();
		case C_NUMBER : return parse_number_node();
		case C_OPEN_PAREN : return parse_paren_node();
	}
}

expr_node* parser::parse_bin_op_rhs(int prev_type, expr_node* lhs) { // a + b * c
	PRINT("parse_bin_op_rhs");
	while (1) {
		int cur_precedence = get_op_precedence();

		if (cur_precedence < prev_type)
			return lhs;

		std::string op = CUR_TOKEN_NAME;
		get_next_token(); // skip binop

		expr_node* rhs = parse_primary();
		if (!rhs)	return 0;

		c_ttype next_type = CUR_TOKEN_TYPE;
		if (cur_precedence < next_type) {
			rhs = parse_bin_op_rhs(cur_precedence + 1, rhs);
			if (rhs == 0)	return 0;
		}

		lhs = new binary_expr_node(op, lhs, rhs);
	}
}

expr_node* parser::parse_expr() {
	PRINT("parse_expr");
	expr_node* lhs = parse_primary();
	if (!lhs) return 0;

	return parse_bin_op_rhs(0, lhs);
}

expr_node* parser::parse_for_loop_expr() {
	get_next_token(); // skip 'for'
	expr_node *init = nullptr, *compare = nullptr, *update = nullptr;
	
	if (CUR_TOKEN_TYPE != C_OPEN_PAREN) {
		return Error("expected '(' in for-loop ");
	}
	
	get_next_token(); // skip '(' 
	
	if (CUR_TOKEN_TYPE != C_SEMICOLON) { // init is not empty
		init = parse_expr();
	}
	get_next_token(); // skip the first ';'
	
	if (CUR_TOKEN_TYPE != C_SEMICOLON) { // compare is not empty
		compare = parse_expr();
	}
	
	get_next_token(); // skip the second ';'
	
	if (CUR_TOKEN_TYPE != C_CLOSE_PAREN) { // update is not empty
		update = parse_expr();
	}
	
	if (CUR_TOKEN_TYPE != C_CLOSE_PAREN) {
		return Error("expected ')' in for-loop ");
	}
	
	get_next_token(); // skip the ')'
	
	return new for_loop_node(init, compare, update);
	
}

function_node* parser::parse_top_level_expr() {
	PRINT("parse_top_level_expr");
	if (expr_node* e = parse_expr()) {
		// Make an anonymous proto.
		prototype_node* proto = new prototype_node("", std::vector<std::string>());
		return new function_node(proto, e);
	}
	return 0;
}

void parser::handle_top_level_expr() {
	if (parse_top_level_expr()) {
		std::cout << "Parsed a top-level expr." << std::endl;
	} else {
		get_next_token();
	}
}

void parser::handle_for_loop_expr() {
	if (parse_for_loop_expr()) {
		std::cout << "Parsed a for-loop expr." << std::endl;
	} else {
		get_next_token();
	}
}

void parser::parse_main() {
	get_next_token();
	while(1) {
		switch(CUR_TOKEN_TYPE) {
			default: handle_top_level_expr(); break; // TODO
			case RID_FOR:		handle_for_loop_expr(); break;
			case C_SEMICOLON:	get_next_token(); break;
			case C_EOF: return;
		}
	}
}


/*
prototype_node* parser::parse_prototype() {
	if (CUR_TOKEN_TYPE != C_NAME)
		return ErrorP("Expected function name in prototype");

	std::string name = CUR_TOKEN_NAME;
	get_next_token();

	if (CUR_TOKEN_TYPE != C_OPEN_PAREN)
		return ErrorP("Expected '(' in prototype");

	std::vector<std::string> arg_names;
	while (get_next_token() == C_NAME)
		arg_names.push_back(CUR_TOKEN_NAME);
	if (CUR_TOKEN_TYPE != C_CLOSE_PAREN)
		return ErrorP("Expected ')' in prototype");

	get_next_token(); // skip ')'

	return new prototype_node(name, arg_names);
}

function_node* parser::parse_definition() {
	get_next_token();

	prototype_node* proto = parse_prototype();
	if (proto == 0) return 0;

	if (expr_node* e = parse_expr())
		return new function_node(proto, e);
	return 0;
}

void parser::handle_definition() {
	if (parse_definition()) {
		std::cout << "Parsed a function definition." << std::endl;
	} else {
		get_next_token();
	}
}
*/