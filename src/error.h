#ifndef LAMBLEXER_ERROR_H_
#define LAMBLEXER_ERROR_H_


#define ERROR(ERR_ID) std::cout << "line: " << cur_line_info.linenum << " error: " << error_string[ERR_ID] << std::endl

/*
 * error code of parsing
 */
enum ERROR_ID {
	NO_ERROR = 0,
	INVALID_IDENTIFIER,
	UNKNOWN_TYPE,
	TOO_LONG_IDENTIFIER,
	NON_HEX_NUMBER_START_WITH_ZERO,
};

/*
 * error string
 */
const std::string error_string[] {
	" no error ",
	" invalid identifier ",
	" unknown type name ",
	" this identifier is too long ",
	" non-hex number can't start with 0 ",
};

#endif /* end of LAMBLEXER_ERROR_H_ */