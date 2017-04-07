#ifndef TOKEN_H_
#define TOKEN_H_

/*
 * error code of parsing
 */
enum ERROR_ID {
	NO_ERROR = 0,
	INVALID_IDENTIFIER, // 1
	UNKNOWN_TYPE, // 2
	TOO_LONG_IDENTIFIER, // 3
};

/*
 * error string
 */
const std::string error_string[] {
	" parse success ",
	" invalid identifier ",
	" unknown type name ",
	" this identifier is too long ",
};


#endif /* end of TOKEN_H_ */