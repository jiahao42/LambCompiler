#include "lex_config.h"
#include "token.h"

std::unordered_map<std::string, enum rid> keyword;

struct c_token
{
  unsigned int line;			/* Logical line of first char of token.  */
  unsigned short col;			/* Column of first char of token.  */
  c_ttype type;					/* token type */
  std::string name;				/* identifier */
};