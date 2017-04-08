#ifndef TOKEN_H_
#define TOKEN_H_


#define ERROR(ERR_ID) std::cout << "line: " << cur_line_info.linenum << " error: " << error_string[ERR_ID] << std::endl;
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


/* 
 * Reserved identifiers.  This is the union of all the keywords for C,
 */

enum rid
{
  /* Modifiers: */
  /* C, in empirical order of frequency.  */
  RID_STATIC = 0,
  RID_UNSIGNED, RID_LONG,    RID_CONST, RID_EXTERN,
  RID_REGISTER, RID_TYPEDEF, RID_SHORT, RID_INLINE,
  RID_VOLATILE, RID_SIGNED,  RID_AUTO,  RID_RESTRICT,

  /* C */
  RID_INT,     RID_CHAR,   RID_FLOAT,    RID_DOUBLE, RID_VOID,
  RID_ENUM,    RID_STRUCT, RID_UNION,    RID_IF,     RID_ELSE,
  RID_WHILE,   RID_DO,     RID_FOR,      RID_SWITCH, RID_CASE,
  RID_DEFAULT, RID_BREAK,  RID_CONTINUE, RID_RETURN, RID_GOTO,
  RID_SIZEOF,

  RID_FUNCTION_NAME
};




#endif /* end of TOKEN_H_ */






