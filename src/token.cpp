#include "lex_config.h"
#include "token.h"


#if 0
/*
 *	35 keywords here
 */
enum rid
{
  /* Modifiers: */
  /* C, in empirical order of frequency.  */
  RID_STATIC = 0,
  RID_UNSIGNED, RID_LONG,    RID_CONST, RID_EXTERN,
  RID_REGISTER, RID_TYPEDEF, RID_SHORT, RID_INLINE,
  RID_VOLATILE, RID_SIGNED,  RID_AUTO,  RID_RESTRICT,

  /* C */
  RID_INT,     RID_CHAR,   RID_FLOAT,    RID_DOUBLE, RID_VOID,
  RID_ENUM,    RID_STRUCT, RID_UNION,    RID_IF,     RID_ELSE,
  RID_WHILE,   RID_DO,     RID_FOR,      RID_SWITCH, RID_CASE,
  RID_DEFAULT, RID_BREAK,  RID_CONTINUE, RID_RETURN, RID_GOTO,
  RID_SIZEOF,

  RID_FUNCTION_NAME,
};
#endif

/*
 * TODO: must implement a custom hashtable for keywords
 * unordered_map takes up too much memory
 */
#define PAIR(string, rid) {"string", rid}
std::unordered_map<std::string, enum rid> keyword (
	{
		PAIR(static, RID_STATIC),
		PAIR(unsigned, RID_UNSIGNED),
		PAIR(long, RID_LONG),
		PAIR(const, RID_CONST),
		PAIR(extern, RID_EXTERN),
		PAIR(register, RID_REGISTER),
		PAIR(typedef, RID_TYPEDEF),
		PAIR(short, RID_SHORT),
		PAIR(inline, RID_INLINE),
		PAIR(volatile, RID_VOLATILE),
		PAIR(signed, RID_SIGNED),
		PAIR(auto, RID_AUTO),
		PAIR(restrict, RID_RESTRICT),
		PAIR(int, RID_INT),
		PAIR(char, RID_CHAR),
		PAIR(float, RID_FLOAT),
		PAIR(double, RID_DOUBLE),
		PAIR(void, RID_VOID),
		PAIR(enum, RID_ENUM),
		PAIR(struct, RID_STRUCT),
		PAIR(union, RID_UNION),
		PAIR(if, RID_IF),
		PAIR(else, RID_ELSE),
		PAIR(while, RID_WHILE),
		PAIR(do, RID_DO),
		PAIR(for, RID_FOR),
		PAIR(switch, RID_SWITCH),
		PAIR(case, RID_SWITCH),
		PAIR(default, RID_DEFAULT),
		PAIR(break, RID_BREAK),
		PAIR(continue, RID_CONTINUE),
		PAIR(return, RID_RETURN),
		PAIR(goto, RID_GOTO),
		PAIR(sizeof, RID_SIZEOF),
		PAIR(function, RID_FUNCTION_NAME),
	}
);
#undef PAIR













