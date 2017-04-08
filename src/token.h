#ifndef TOKEN_H_
#define TOKEN_H_


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
 * Reserved identifiers.  This is the union of some keywords for C,
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


#define TTYPE_TABLE				\
  OP(CPP_EQ = 0,	"=")			\
  OP(CPP_NOT,		"!")			\
  OP(CPP_GREATER,	">")	/* compare */	\
  OP(CPP_LESS,		"<")			\
  OP(CPP_PLUS,		"+")	/* math */	\
  OP(CPP_MINUS,		"-")			\
  OP(CPP_MULT,		"*")			\
  OP(CPP_DIV,		"/")			\
  OP(CPP_MOD,		"%")			\
  OP(CPP_AND,		"&")	/* bit ops */	\
  OP(CPP_OR,		"|")			\
  OP(CPP_XOR,		"^")			\
  OP(CPP_RSHIFT,	">>")			\
  OP(CPP_LSHIFT,	"<<")			\
  OP(CPP_MIN,		"<?")	/* extension */	\
  OP(CPP_MAX,		">?")			\
\
  OP(CPP_COMPL,		"~")			\
  OP(CPP_AND_AND,	"&&")	/* logical */	\
  OP(CPP_OR_OR,		"||")			\
  OP(CPP_QUERY,		"?")			\
  OP(CPP_COLON,		":")			\
  OP(CPP_COMMA,		",")	/* grouping */	\
  OP(CPP_OPEN_PAREN,	"(")			\
  OP(CPP_CLOSE_PAREN,	")")			\
  OP(CPP_EQ_EQ,		"==")	/* compare */	\
  OP(CPP_NOT_EQ,	"!=")			\
  OP(CPP_GREATER_EQ,	">=")			\
  OP(CPP_LESS_EQ,	"<=")			\
\
  OP(CPP_PLUS_EQ,	"+=")	/* math */	\
  OP(CPP_MINUS_EQ,	"-=")			\
  OP(CPP_MULT_EQ,	"*=")			\
  OP(CPP_DIV_EQ,	"/=")			\
  OP(CPP_MOD_EQ,	"%=")			\
  OP(CPP_AND_EQ,	"&=")	/* bit ops */	\
  OP(CPP_OR_EQ,		"|=")			\
  OP(CPP_XOR_EQ,	"^=")			\
  OP(CPP_RSHIFT_EQ,	">>=")			\
  OP(CPP_LSHIFT_EQ,	"<<=")			\
  OP(CPP_MIN_EQ,	"<?=")	/* extension */	\
  OP(CPP_MAX_EQ,	">?=")			\
  /* Digraphs together, beginning with CPP_FIRST_DIGRAPH.  */	\
  OP(CPP_HASH,		"#")	/* digraphs */	\
  OP(CPP_PASTE,		"##")			\
  OP(CPP_OPEN_SQUARE,	"[")			\
  OP(CPP_CLOSE_SQUARE,	"]")			\
  OP(CPP_OPEN_BRACE,	"{")			\
  OP(CPP_CLOSE_BRACE,	"}")			\
  /* The remainder of the punctuation.  Order is not significant.  */	\
  OP(CPP_SEMICOLON,	";")	/* structure */	\
  OP(CPP_ELLIPSIS,	"...")			\
  OP(CPP_PLUS_PLUS,	"++")	/* increment */	\
  OP(CPP_MINUS_MINUS,	"--")			\
  OP(CPP_DEREF,		"->")	/* accessors */	\
  OP(CPP_DOT,		".")			\
  OP(CPP_SCOPE,		"::")			\
  OP(CPP_DEREF_STAR,	"->*")			\
  OP(CPP_DOT_STAR,	".*")			\
  OP(CPP_ATSIGN,	"@")  /* used in Objective C */ \
\
  TK(CPP_NAME,		SPELL_IDENT)	/* word */			\
  TK(CPP_NUMBER,	SPELL_NUMBER)	/* 34_be+ta  */			\
\
  TK(CPP_CHAR,		SPELL_STRING)	/* 'char' */			\
  TK(CPP_WCHAR,		SPELL_STRING)	/* L'char' */			\
  TK(CPP_OTHER,		SPELL_CHAR)	/* stray punctuation */		\
\
  TK(CPP_STRING,	SPELL_STRING)	/* "string" */			\
  TK(CPP_WSTRING,	SPELL_STRING)	/* L"string" */			\
  TK(CPP_HEADER_NAME,	SPELL_STRING)	/* <stdio.h> in #include */	\
\
  TK(CPP_COMMENT,	SPELL_NUMBER)	/* Only if output comments.  */ \
                                        /* SPELL_NUMBER happens to DTRT.  */ \
  TK(CPP_MACRO_ARG,	SPELL_NONE)	/* Macro argument.  */		\
  TK(CPP_PADDING,	SPELL_NONE)	/* Whitespace for cpp0.  */	\
  TK(CPP_EOF,		SPELL_NONE)	/* End of line or file.  */

#define OP(e, s) e,
#define TK(e, s) e,
enum cpp_ttype
{
  TTYPE_TABLE
  N_TTYPES
};
#undef OP
#undef TK



#endif /* end of TOKEN_H_ */






