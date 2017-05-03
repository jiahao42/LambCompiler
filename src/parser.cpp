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


c_token& parser::get_next_token() {
	cur_token = source_file.c_token_vector[token_idx++];
	std::cout << "idx: " << token_idx << " " << CUR_TOKEN_NAME << std::endl;
	return cur_token;
}


expr_node* parser::parse_identifier_node() {
	std::string name = CUR_TOKEN_NAME;
	get_next_token(); // skip identifier
	if (CUR_TOKEN_TYPE != C_OPEN_PAREN)
		return new var_expr_node(name);
	
	get_next_token(); // skip '('
	std::vector<expr_node*> args;
	if (CUR_TOKEN_TYPE != C_CLOSE_PAREN) {
		while (1) {
			expr_node* arg = parse_expr();
			if (!arg) return 0;
			args.push_back(arg);
			
			if (CUR_TOKEN_TYPE == C_OPEN_PAREN)
				break;
			
			if (CUR_TOKEN_TYPE != C_COMMA)
				return 0;
			get_next_token();
		}
	}
	
	// skip ')'
	get_next_token();
	
	return new call_expr_node(name, args);
}

expr_node* parser::parse_number_node() {
	double val = stoi(CUR_TOKEN_NAME);
	expr_node* res = new number_expr_node(val);
	get_next_token();
	return res;
}

expr_node* parser::parse_paren_node() {
	get_next_token(); //skip '('
	expr_node* node = parse_expr();
	if (!node) return 0;
	
	if (CUR_TOKEN_TYPE != C_CLOSE_PAREN)
		return 0;
	get_next_token();
	return node;
}

expr_node* parser::parse_primary() {
	c_ttype cur_type = CUR_TOKEN_TYPE;
	switch (cur_type) {
		default: return 0;
		case C_NAME: return parse_identifier_node();
		case C_NUMBER : return parse_number_node();
		case C_OPEN_PAREN : return parse_paren_node();
	}
}

expr_node* parser::parse_bin_op_rhs(c_ttype prev_type, expr_node* lhs) {
	while (1) {
		//c_ttype prev_type = token.get_type();
		c_ttype cur_type = CUR_TOKEN_TYPE;
		
		if (cur_type < prev_type)
			return lhs;
		
		std::string op = CUR_TOKEN_NAME;
		get_next_token();
		
		expr_node* rhs = parse_primary();
		if (!rhs)	return 0;
		
		c_ttype next_type = CUR_TOKEN_TYPE;
		if (cur_type < next_type) {
			int tmp = static_cast<int>(cur_type);
			rhs = parse_bin_op_rhs(static_cast<c_ttype>(tmp + 1), rhs);
			if (rhs == 0)	return 0;
		}
		
		lhs = new binary_expr_node(op, lhs, rhs);
	}
}

expr_node* parser::parse_expr() {
	expr_node* lhs = parse_primary();
	if (!lhs) return 0;
	
	return parse_bin_op_rhs(static_cast<c_ttype>(0), lhs);
}


prototype_node* parser::parse_prototype() {
	if (!(CUR_TOKEN_TYPE == C_NAME))
		return 0;
	
	std::string name = CUR_TOKEN_NAME;
	get_next_token();
	
	if (CUR_TOKEN_TYPE != C_OPEN_PAREN) 
		return 0;
	
	std::vector<std::string> arg_names;
	while (CUR_TOKEN_TYPE == C_NAME)
		arg_names.push_back(CUR_TOKEN_NAME);
	if (CUR_TOKEN_TYPE != C_CLOSE_PAREN)
		return 0;
	
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
	while(1) {
		switch(CUR_TOKEN_TYPE) {
			case C_SEMICOLON:	get_next_token(); break;
			case C_NAME: handle_definition(); break;
			case C_OTHER: return;
			default: handle_top_level_expr(); break;
		}
	}
}

















