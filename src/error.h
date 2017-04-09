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
	NON_HEX_NUMBER_START_WITH_ZERO,
};

/*
 * error string
 */
const std::string ERROR_STRING[] = {
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
};

/*
 * warning string
 */
const std::string WARNING_STRING[] = {
	" character constant too long for its type ",
};

/*
 * For the error queue, see error.cpp
 */
typedef struct _error {
	_error(enum ERROR_ID _ERROR_ID, size_t _linenum, size_t _col) : ERROR_ID(_ERROR_ID), linenum(_linenum), col(_col) {}
	enum ERROR_ID;
	size_t linenum;
	size_t col;
	friend std::ostream& operator <<(std::ostream& output, const _error e) {
		std::cout << ":" << e.linenum << ":" << e.col << " type: " << c.type << " value: " << c.name << std::endl;
		return output;
	}
}_error;

/*
 * For the warning queue, see error.cpp
 */
typedef struct _warning {
	_warning(enum WARING_ID _WARING_ID, size_t _linenum, size_t _col) : WARING_ID(_WARING_ID), linenum(_linenum), col(_col) {}
	enum WARING_ID;
	size_t linenum;
	size_t col;
}_warning;



#endif /* end of LAMBLEXER_ERROR_H_ */