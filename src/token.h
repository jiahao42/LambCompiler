#ifndef TOKEN_H_
#define TOKEN_H_

/*
 * error code of parsing
 */
enum ERROR_ID {
	NO_ERROR = -1,
	INVALID_IDENTIFIER = 0, // 0
	UNKNOWN_TYPE, // 1
};

/*
 * error string
 */
const std::string error_string[2] {
	"invalid identifier ",
	"unknown type name ",
};


enum RID {
  Num = 128, Fun, Sys, Glo, Loc, Id,
  Char, Else, Enum, If, Int, Return, Sizeof, While,
  Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};

#endif