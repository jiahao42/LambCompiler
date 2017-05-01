//LambLexer
//by James 2017/04/06

#ifndef LAMBLEXER_TOKEN_H_
#define LAMBLEXER_TOKEN_H_

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

  RID_FUNCTION_NAME,
};

/*
 * Token Type Table
 */
#define TTYPE_TABLE				\
  OP(C_EQ = 0,	"=")			\
  OP(C_NOT,		"!")			\
  OP(C_GREATER,	">")	/* compare */	\
  OP(C_LESS,		"<")			\
  OP(C_PLUS,		"+")	/* math */	\
  OP(C_MINUS,		"-")			\
  OP(C_MULT,		"*")			\
  OP(C_DIV,		"/")			\
  OP(C_MOD,		"%")			\
  OP(C_AND,		"&")	/* bit ops */	\
  OP(C_OR,		"|")			\
  OP(C_XOR,		"^")			\
  OP(C_RSHIFT,	">>")			\
  OP(C_LSHIFT,	"<<")			\
\
  OP(C_COMPL,		"~")			\
  OP(C_AND_AND,	"&&")	/* logical */	\
  OP(C_OR_OR,		"||")			\
  OP(C_QUERY,		"?")			\
  OP(C_COLON,		":")			\
  OP(C_COMMA,		",")	/* grouping */	\
  OP(C_OPEN_PAREN,	"(")			\
  OP(C_CLOSE_PAREN,	")")			\
  OP(C_EQ_EQ,		"==")	/* compare */	\
  OP(C_NOT_EQ,	"!=")			\
  OP(C_GREATER_EQ,	">=")			\
  OP(C_LESS_EQ,	"<=")			\
\
  OP(C_PLUS_EQ,	"+=")	/* math */	\
  OP(C_MINUS_EQ,	"-=")			\
  OP(C_MULT_EQ,	"*=")			\
  OP(C_DIV_EQ,	"/=")			\
  OP(C_MOD_EQ,	"%=")			\
  OP(C_AND_EQ,	"&=")	/* bit ops */	\
  OP(C_OR_EQ,		"|=")			\
  OP(C_XOR_EQ,	"^=")			\
  OP(C_RSHIFT_EQ,	">>=")			\
  OP(C_LSHIFT_EQ,	"<<=")			\
  OP(C_OPEN_SQUARE,	"[")			\
  OP(C_CLOSE_SQUARE,	"]")			\
  OP(C_OPEN_BRACE,	"{")			\
  OP(C_CLOSE_BRACE,	"}")			\
  /* The remainder of the punctuation.  Order is not significant.  */	\
  OP(C_SEMICOLON,	";")	/* structure */	\
  OP(C_PLUS_PLUS,	"++")	/* increment */	\
  OP(C_MINUS_MINUS,	"--")			\
  OP(C_DEREF,		"->")	/* accessors */	\
  OP(C_DOT,		".")			\
  OP(C_SCOPE,		"::")			\
\
  TK(C_NAME,		SPELL_IDENT)	/* word */			\
  TK(C_NUMBER,	SPELL_NUMBER)	/* 34_be+ta  */			\
\
  TK(C_CHAR,		SPELL_STRING)	/* 'char' */			\
  TK(C_OTHER,		SPELL_CHAR)	/* stray punctuation */		\
\
  TK(C_STRING,	SPELL_STRING)	/* "string" */			\
  TK(C_HEADER_NAME,	SPELL_STRING)	/* <stdio.h> in #include */	\
\
  TK(C_COMMENT,	SPELL_NUMBER)	/* Only if output comments.  */ \
                                        /* SPELL_NUMBER happens to DTRT.  */ \
  TK(C_PADDING,	SPELL_NONE)	/* Whitespace for cpp0.  */	\
  TK(C_EOF,		SPELL_NONE)	/* End of line or file.  */ 
  
 
#define OP(e, s) e,
#define TK(e, s) e,
enum c_ttype
{
  TTYPE_TABLE
  N_TTYPES
};
#undef OP
#undef TK

enum c_ttype;

typedef struct c_token
{
	size_t line;					/* Logical line of first char of token.  */
	size_t col;						/* Column of first char of token.  */
	c_ttype type;					/* Token type */
	std::string name;				/* Identifier */
	
	c_token() {}
	c_token(size_t _line) : line(_line) {}
	c_token(size_t _line, size_t _col, c_ttype _type, std::string _name) : line(_line), col(_col), type(_type), name(_name) {}
	friend std::ostream& operator <<(std::ostream& output, const c_token c) {
		std::cout << ":" << c.line << ":" << c.col << " type: " << c.type << " value: " << c.name;
		return output;
	}
	inline void set(size_t _col, c_ttype _type, std::string _name) {
		col = _col;
		type = _type;
		name = _name;
	}
	inline void set_line(size_t _line) {
		line = _line;
	}
	inline c_ttype& get_type() {
		return type;
	}
}c_token;

#endif /* end of LAMBLEXER_TOKEN_H_ */






