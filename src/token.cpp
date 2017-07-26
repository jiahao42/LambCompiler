// LambLexer
// by James 2017/04/06

#include "token.h"
#include "config.h"


/*
 * TODO: must implement a custom hashtable for keywords
 * unordered_map takes up too much memory
 */
#define PAIR(string, c_ttype)                                                  \
    { string, c_ttype }
std::unordered_map<std::string, enum c_ttype> keyword({
    PAIR("static", RID_STATIC),
    PAIR("unsigned", RID_UNSIGNED),
    PAIR("long", RID_LONG),
    PAIR("const", RID_CONST),
    PAIR("extern", RID_EXTERN),
    PAIR("short", RID_SHORT),
    PAIR("volatile", RID_VOLATILE),
    PAIR("signed", RID_SIGNED),
    PAIR("auto", RID_AUTO),
    PAIR("int", RID_INT),
    PAIR("char", RID_CHAR),
    PAIR("float", RID_FLOAT),
    PAIR("double", RID_DOUBLE),
    PAIR("void", RID_VOID),
    PAIR("enum", RID_ENUM),
    PAIR("struct", RID_STRUCT),
    PAIR("union", RID_UNION),
    PAIR("if", RID_IF),
    PAIR("else", RID_ELSE),
    PAIR("while", RID_WHILE),
    PAIR("do", RID_DO),
    PAIR("for", RID_FOR),
    PAIR("switch", RID_SWITCH),
    PAIR("case", RID_CASE),
    PAIR("default", RID_DEFAULT),
    PAIR("break", RID_BREAK),
    PAIR("continue", RID_CONTINUE),
    PAIR("return", RID_RETURN),
    PAIR("goto", RID_GOTO),
    PAIR("sizeof", RID_SIZEOF),
});
#undef PAIR
