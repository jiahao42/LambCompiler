#ifndef TOKEN_H_
#define TOKEN_H_

enum ERROR_ID {
	INVALID_IDENTIFIER = 0,
	UNKNOWN_TYPE,
};

const std::string errors[2] {
	"invalid identifier ",
	"unknown type name ",
};

#endif