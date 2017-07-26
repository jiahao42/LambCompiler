// LambLexer
// by James 2017/04/06

#ifndef LAMB_COMPILER_TOKEN_H_
#define LAMB_COMPILER_TOKEN_H_

/*
 * Token Type Table
 */
#define TTYPE_TABLE                                                            \
    OP(C_EQ = 0, "=")                                                          \
    OP(C_NOT, "!")                                                             \
    /* compare */                                                              \
    OP(C_GREATER, ">")                                                         \
    OP(C_LESS, "<")                                                            \
    /* math */                                                                 \
    OP(C_PLUS, "+")                                                            \
    OP(C_MINUS, "-")                                                           \
    OP(C_MULT, "*")                                                            \
    OP(C_DIV, "/")                                                             \
    OP(C_MOD, "%")                                                             \
    /* bit ops */                                                              \
    OP(C_AND, "&")                                                             \
    OP(C_OR, "|")                                                              \
    OP(C_XOR, "^")                                                             \
    OP(C_RSHIFT, ">>")                                                         \
    OP(C_LSHIFT, "<<")                                                         \
                                                                               \
    OP(C_COMPL, "~")                                                           \
    /* logical */                                                              \
    OP(C_AND_AND, "&&")                                                        \
    OP(C_OR_OR, "||")                                                          \
    OP(C_QUERY, "?")                                                           \
    OP(C_COLON, ":")                                                           \
    /* grouping */                                                             \
    OP(C_COMMA, ",")                                                           \
    OP(C_OPEN_PAREN, "(")                                                      \
    OP(C_CLOSE_PAREN, ")")                                                     \
    /* compare */                                                              \
    OP(C_EQ_EQ, "==")                                                          \
    OP(C_NOT_EQ, "!=")                                                         \
    OP(C_GREATER_EQ, ">=")                                                     \
    OP(C_LESS_EQ, "<=")                                                        \
                                                                               \
    /* math */                                                                 \
    OP(C_PLUS_EQ, "+=")                                                        \
    OP(C_MINUS_EQ, "-=")                                                       \
    OP(C_MULT_EQ, "*=")                                                        \
    OP(C_DIV_EQ, "/=")                                                         \
    OP(C_MOD_EQ, "%=")                                                         \
    /* bit ops */                                                              \
    OP(C_AND_EQ, "&=")                                                         \
    OP(C_OR_EQ, "|=")                                                          \
    OP(C_XOR_EQ, "^=")                                                         \
    OP(C_RSHIFT_EQ, ">>=")                                                     \
    OP(C_LSHIFT_EQ, "<<=")                                                     \
    OP(C_OPEN_SQUARE, "[")                                                     \
    OP(C_CLOSE_SQUARE, "]")                                                    \
    OP(C_OPEN_BRACE, "{")                                                      \
    OP(C_CLOSE_BRACE, "}")                                                     \
    /* The remainder of the punctuation.  Order is not significant.  */        \
    OP(C_SEMICOLON, ";")  /* structure */                                      \
    OP(C_PLUS_PLUS, "++") /* increment */                                      \
    OP(C_MINUS_MINUS, "--")                                                    \
    OP(C_DEREF, "->") /* accessors */                                          \
    OP(C_DOT, ".")                                                             \
    OP(C_SCOPE, "::")                                                          \
                                                                               \
    TK(C_NAME, SPELL_IDENT)    /* word */                                      \
    TK(C_NUMBER, SPELL_NUMBER) /* 34_be+ta  */                                 \
                                                                               \
    TK(C_CHAR, SPELL_STRING) /* 'char' */                                      \
    TK(C_OTHER, SPELL_CHAR)  /* stray punctuation */                           \
                                                                               \
    TK(C_STRING, SPELL_STRING)      /* "string" */                             \
    TK(C_HEADER_NAME, SPELL_STRING) /* <stdio.h> in #include */                \
                                                                               \
    TK(C_COMMENT, SPELL_NUMBER) /* Only if output comments.  */                \
                                /* SPELL_NUMBER happens to DTRT.  */           \
    TK(C_PADDING, SPELL_NONE)   /* Whitespace for cpp0.  */                    \
    TK(C_EOF, SPELL_NONE)       /* End of line or file.  */                    \
    /* Modifiers: */                                                           \
    TK(RID_STATIC = 100, "static")                                             \
    TK(RID_UNSIGNED, "unsigned")                                               \
    TK(RID_LONG, "long")                                                       \
    TK(RID_CONST, "const")                                                     \
    TK(RID_EXTERN, "extern")                                                   \
    TK(RID_SHORT, "short")                                                     \
    TK(RID_VOLATILE, "volatile")                                               \
    TK(RID_SIGNED, "signed")                                                   \
    TK(RID_AUTO, "auto")                                                       \
                                                                               \
    /* Built-in type */                                                        \
    TK(RID_INT, "int")                                                         \
    TK(RID_CHAR, "char")                                                       \
    TK(RID_FLOAT, "float")                                                     \
    TK(RID_DOUBLE, "double")                                                   \
    TK(RID_VOID, "void")                                                       \
    TK(RID_ENUM, "enum")                                                       \
    TK(RID_STRUCT, "struct")                                                   \
    TK(RID_UNION, "union")                                                     \
                                                                               \
    /* Control flow */                                                         \
    TK(RID_WHILE, "while")                                                     \
    TK(RID_DO, "do")                                                           \
    TK(RID_FOR, "for")                                                         \
    TK(RID_GOTO, "goto")                                                       \
    TK(RID_SWITCH, "switch")                                                   \
    TK(RID_CASE, "case")                                                       \
    TK(RID_DEFAULT, "default")                                                 \
    TK(RID_BREAK, "break")                                                     \
    TK(RID_IF, "if")                                                           \
    TK(RID_ELSE, "else")                                                       \
    TK(RID_CONTINUE, "continue")                                               \
    TK(RID_RETURN, "return")                                                   \
                                                                               \
    /* Others */                                                               \
    TK(RID_SIZEOF, "sizeof")                                                   \
    TK(RID_FUNCTION_NAME = 130, FUNCTION_NAME)

#define OP(e, s) e,
#define TK(e, s) e,
enum c_ttype { TTYPE_TABLE N_TTYPES };
#undef OP
#undef TK

enum c_ttype;

typedef struct c_token {
    size_t line;      /* Logical line of first char of token.  */
    size_t col;       /* Column of first char of token.  */
    c_ttype type;     /* Token type */
    std::string name; /* Identifier */

    c_token() {}
    c_token(size_t _line) : line(_line) {}
    c_token(size_t _line, size_t _col, c_ttype _type, std::string _name)
        : line(_line), col(_col), type(_type), name(_name) {}
    friend std::ostream &operator<<(std::ostream &output, const c_token c) {
        std::cout << ":" << c.line << ":" << c.col << " type: " << c.type
                  << " value: " << c.name;
        return output;
    }
    inline void set(size_t _col, c_ttype _type, std::string _name) {
        col = _col;
        type = _type;
        name = _name;
    }
    inline void set_line(size_t _line) { line = _line; }
    inline c_ttype &get_type() { return type; }
    inline std::string &get_name() { return name; }
    inline void set_type(c_ttype _type) { type = _type; }
    inline size_t &get_line() { return line; }
    inline size_t &get_col() { return col; }
} c_token;

#endif /* end of LAMB_COMPILER_TOKEN_H_ */
