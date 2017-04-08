#ifndef LAMBLEXER_ERROR_H_
#define LAMBLEXER_ERROR_H_

/*
 * error code of parsing
 */
enum ERROR_ID {
	NO_ERROR = 0,
	INVALID_IDENTIFIER,
	UNKNOWN_TYPE,
	TOO_LONG_IDENTIFIER,
};

/*
 * error string
 */
const std::string error_string[] {
	" no error ",
	" invalid identifier ",
	" unknown type name ",
	" this identifier is too long ",
};

#endif /* end of LAMBLEXER_ERROR_H_ */