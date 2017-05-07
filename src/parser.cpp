//LambCompiler
//by James 2017/05/02
#include "parser_config.h"
#include "parser.h"


/*
 * Push error into the queue
 */
#define PUSH_ERROR(linenum, col, ERR_ID) \
	do {\
		_error e(ERR_ID, linenum, col);\
		error_queue.push(e);\
	}while(0)

/*
 * Push warning into the queue
 */
#define PUSH_WARNING(linenum, col, WARNING_ID) \
	do {\
		_warning w(WARNING_ID, linenum, col);\
		warning_queue.push(w);\
	}while(0)

/*
 * Pop the error from error queue and output the error to the console
 */
#define POP_ERROR() \
	do {\
		while(!error_queue.empty()) {\
			std::cout << error_queue.front();\
			error_queue.pop();\
		}\
	}while(0)

/*
 * Pop the warning from error queue and output the warning to the console
 */
#define POP_WARNING() \
	do {\
		while(!warning_queue.empty()) {\
			std::cout << warning_queue.front();\
			warning_queue.pop();\
		}\
	}while(0)

#define CUR_TOKEN_TYPE cur_token.get_type()
#define CUR_TOKEN_NAME cur_token.get_name()
std::queue<_error> error_queue;		/* A queue used for storing error */
std::queue<_warning> warning_queue; /* A queue used for storing warning */
extern source source_file;


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

expr_node *Error(const char *str) { fprintf(stderr, "Error: %s\n", str);return 0;}
prototype_node *ErrorP(const char *str) { Error(str); return 0; }
function_node *ErrorF(const char *str) { Error(str); return 0; }

expr_node* parser::parse_identifier_node() {
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
	double val = stod(CUR_TOKEN_NAME);
	expr_node* res = new number_expr_node(val);
	get_next_token();
	return res;
}

expr_node* parser::parse_paren_node() {
	get_next_token(); //skip '('
	expr_node* node = parse_expr();
	if (!node) return 0;

	if (CUR_TOKEN_TYPE != C_CLOSE_PAREN)
		return Error("expected ')'");
	get_next_token();
	return node;
}

expr_node* parser::parse_primary() {
	c_ttype cur_type = CUR_TOKEN_TYPE;
	switch (cur_type) {
		default: return Error("unknown token when expecting an expression");
		case C_NAME: return parse_identifier_node();
		case C_NUMBER : return parse_number_node();
		case C_OPEN_PAREN : return parse_paren_node();
	}
}

expr_node* parser::parse_bin_op_rhs(int prev_type, expr_node* lhs) {
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
	expr_node* lhs = parse_primary();
	if (!lhs) return 0;

	return parse_bin_op_rhs(0, lhs);
}


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


function_node* parser::parse_top_level_expr() {
	if (expr_node* e = parse_expr()) {
		// Make an anonymous proto.
		prototype_node* proto = new prototype_node("", std::vector<std::string>());
		return new function_node(proto, e);
	}
	return 0;
}

void parser::handle_definition() {
	if (parse_definition()) {
		std::cout << "Parsed a function definition." << std::endl;
	} else {
		get_next_token();
	}
}


void parser::handle_top_level_expr() {
	if (parse_top_level_expr()) {
		std::cout << "Parsed a top-level expr." << std::endl;
	} else {
		get_next_token();
	}
}

void parser::main_loop() {
	get_next_token();
	while(1) {
		switch(CUR_TOKEN_TYPE) {
			default: handle_top_level_expr(); break; // TODO
			case C_SEMICOLON:	get_next_token(); break;
			case C_EOF: return;
		}
	}
}
