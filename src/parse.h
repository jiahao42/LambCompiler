//LambCompiler
//by James 2017/05/01

#include "lex.h"

class parser {
private:
	int token_idx;
	c_token cur_token;
	
public:
	c_token& get_next_token();
	inline bool get_token_precedence();
}