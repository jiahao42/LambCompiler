#include "lex_config.h"
#include "token.h"

std::unordered_map<std::string, enum rid> keyword;

struct c_token
{
	size_t line;			/* Logical line of first char of token.  */
	size_t col;			/* Column of first char of token.  */
	c_ttype type;					/* token type */
	union {
		std::string name;				/* identifier */
		char unknown;							/* unknown character */
	}val;
	
	c_token(size_t _line, size_t _col, c_ttype _type, std::string _name) : line(_line), col(_col), c_ttype(_type), val.name(_name) {}
	c_token(size_t _line, size_t _col, c_ttype _type, char _unknown) : line(_line), col(_col), c_ttype(_type), val.unknown(_unknown) {}
};