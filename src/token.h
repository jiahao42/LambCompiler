#ifndef TOKEN_H_
#define TOKEN_H_

/*
 * error code of parsing
 */
enum ERROR_ID {
	NO_ERROR = -1,
	INVALID_IDENTIFIER = 0, // 0
	UNKNOWN_TYPE, // 1
	TOO_LONG_IDENTIFIER,
};

/*
 * error string
 */
const std::string error_string[] {
	"invalid identifier ",
	"unknown type name ",
	"this identifier is too long ",
};


#endif /* end of TOKEN_H_ */