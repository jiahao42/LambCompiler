//LambLexer
//by James 2017/04/06

#ifndef LAMBLEXER_ERROR_H_
#define LAMBLEXER_ERROR_H_

extern source source_file;


/*
 * Error ID of parsing
 */
enum ERROR_ID {
	INVALID_IDENTIFIER = 0,
	UNKNOWN_TYPE,
	TOO_MANY_DECIMAL_POINTS,
	INVALID_OCTAL_NUMBER,
};

/*
 * Error string
 */
const std::string ERROR_STRING[] = {
	" invalid identifier ",
	" unknown type name ",
	" too many decimal points in number ",
	" invalid digit in octal constant ",
};

/*
 * Warning ID of parsing
 */
enum WARING_ID {
	CHAR_TOO_LONG = 0,
	TOO_LONG_IDENTIFIER,
};

/*
 * Warning string
 */
const std::string WARNING_STRING[] = {
	" character constant too long for its type ",
	" the length of identifier is too long ",
};

/*
 * For the error queue, see error.cpp
 */
typedef struct _error {
	_error(ERROR_ID _ERROR_ID, size_t _linenum, size_t _col) : id(_ERROR_ID), linenum(_linenum), col(_col) {}
	ERROR_ID id;
	size_t linenum;
	size_t col;
	friend std::ostream& operator <<(std::ostream& output, const _error e) {
		std::cout << source_file.filename << ":" << e.linenum << ":" << e.col << " Error: " << ERROR_STRING[e.id] << std::endl;
		return output;
	}
}_error;

/*
 * For the warning queue, see error.cpp
 */
typedef struct _warning {
	_warning(WARING_ID _WARING_ID, size_t _linenum, size_t _col) : id(_WARING_ID), linenum(_linenum), col(_col) {}
	
	WARING_ID id;
	size_t linenum;
	size_t col;
	friend std::ostream& operator <<(std::ostream& output, const _warning w) {
		std::cout << source_file.filename << ":" << w.linenum << ":" << w.col << " Warning: " << WARNING_STRING[w.id] << std::endl;
		return output;
	}
}_warning;






#endif /* end of LAMBLEXER_ERROR_H_ */