#include "parser_config.h"
#include "parse.h"


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

std::queue<_error> error_queue;		/* A queue used for storing error */
std::queue<_warning> warning_queue; /* A queue used for storing warning */
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
