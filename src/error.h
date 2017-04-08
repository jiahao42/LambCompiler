#ifndef LAMBLEXER_ERROR_H_
#define LAMBLEXER_ERROR_H_


#define ERROR(ERR_ID, idx) std::cout << source_file.filename << ":" << cur_line_info.linenum << ":" << idx << " Error:" << ERROR_STRING[ERR_ID] << std::endl

#define WARNING(WARNING_ID, idx) std::cout << source_file.filename << ":" << cur_line_info.linenum << ":" << idx << " Warning:" << WARNING_STRING[WARNING_ID] << std::endl

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
const std::string ERROR_STRING[] {
	" no error ",
	" invalid identifier ",
	" unknown type name ",
	" this identifier is too long ",
	" non-hex number can't start with 0 ",
};

/*
 * warning code of parsing
 */
enum WARING_ID {
	CHAR_TOO_LONG = 0,
}

/*
 * warning string
 */
const std::string WARNING_STRING[] {
	" character constant too long for its type ",
}

#endif /* end of LAMBLEXER_ERROR_H_ */