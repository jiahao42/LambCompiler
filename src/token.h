#ifndef TOKEN_H_
#define TOKEN_H_

enum ERROR_ID {
	INVALID_IDENTIFIER = 1,
	UNKNOWN_TYPE, // 2
};

const std::string error_string[2] {
	"invalid identifier ",
	"unknown type name ",
};

#endif