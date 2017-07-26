// LambLexer
// by James 2017/04/06

#ifndef LAMB_COMPILER_ERROR_H_
#define LAMB_COMPILER_ERROR_H_
#include "config.h"

extern source source_file;

/*
 * Error ID of parsing
 */
enum ERROR_ID {
    TOO_MANY_DECIMAL_POINTS = 0,
    INVALID_OCTAL_NUMBER,
    MISSING_TERMINATING_2_QUOTE,
    MISSING_TERMINATING_1_QUOTE,
    UNKNOWN_TYPE,
    INVALID_IDENTIFIER,
};

#define PAIR(error_id, string)                                                 \
    { error_id, string }
static std::map<enum ERROR_ID, std::string> error_table = {
    PAIR(TOO_MANY_DECIMAL_POINTS, " too many decimal points in number "),
    PAIR(INVALID_OCTAL_NUMBER, " invalid digit in octal constant "),
    PAIR(MISSING_TERMINATING_2_QUOTE, " missing terminating \" character "),
    PAIR(UNKNOWN_TYPE, " unknown type name "),
    PAIR(INVALID_IDENTIFIER, " invalid identifier "),
};

#undef PAIR

/*
 * Warning ID of parsing
 */
enum WARING_ID {
    CHAR_TOO_LONG = 0,
    TOO_LONG_IDENTIFIER,
};

#define PAIR(warning_id, string)                                               \
    { warning_id, string }
static std::map<enum WARING_ID, std::string> warning_table = {
    PAIR(CHAR_TOO_LONG, " character constant too long for its type "),
    PAIR(TOO_LONG_IDENTIFIER, " the length of identifier is too long "),
};
#undef PAIR

/*
 * For the error queue
 */
typedef struct _error {
    _error(ERROR_ID _ERROR_ID, size_t _linenum, size_t _col)
        : id(_ERROR_ID), linenum(_linenum), col(_col) {}
    ERROR_ID id;
    size_t linenum;
    size_t col;
    friend std::ostream &operator<<(std::ostream &output, const _error e) {
        auto it = error_table.find(e.id);
        if (it != error_table.end())
            std::cout << source_file.filename << ":" << e.linenum << ":"
                      << e.col << " Error: " << it->second << std::endl;
        else
            std::cout << source_file.filename << ":" << e.linenum << ":"
                      << e.col << " Error: error not found!!!" << std::endl;
        return output;
    }
    ERROR_ID get_error_id() { return id; }
} _error;

/*
 * For the warning queue
 */
typedef struct _warning {
    _warning(WARING_ID _WARING_ID, size_t _linenum, size_t _col)
        : id(_WARING_ID), linenum(_linenum), col(_col) {}

    WARING_ID id;
    size_t linenum;
    size_t col;
    friend std::ostream &operator<<(std::ostream &output, const _warning w) {
        auto it = warning_table.find(w.id);
        if (it != warning_table.end())
            std::cout << source_file.filename << ":" << w.linenum << ":"
                      << w.col << " Warning: " << it->second << std::endl;
        else
            std::cout << source_file.filename << ":" << w.linenum << ":"
                      << w.col << " Warning: warning not found!!!" << std::endl;
        return output;
    }
    WARING_ID get_warning_id() { return id; }
} _warning;

#endif /* end of LAMB_COMPILER_ERROR_H_ */