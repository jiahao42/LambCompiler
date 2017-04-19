//LambLexer
//by James 2017/04/06

#include "lex_config.h"
#include "token.h"
#include "symseg.h"
#include "test.h"
#include "lex.h"
#include "error.h"
#include "util.h"


/*
 * Pop the error from error queue and output the error to the console
 */
#define POP_ERROR() \
	do {\
		while(!error_queue.empty()) {\
			std::cout << error_queue.front();\
			error_queue.pop();\
		}\
	}while(0)

/*
 * Pop the warning from error queue and output the warning to the console
 */
#define POP_WARNING() \
	do {\
		while(!warning_queue.empty()) {\
			std::cout << warning_queue.front();\
			warning_queue.pop();\
		}\
	}while(0)

/*
 * Symbol table, see symseg.h
 */
symbol_root symbol_table;
/*
 * Current file
 */
std::ifstream file;
/*
 * Literally current line
 */
std::string cur_line;
/*
 * Information of current line, including line number and line address
 * See symseg.h
 */
line cur_line_info;
/*
 * Stand for source file, including filename and lines' info
 * See symseg.h
 */
source source_file;

extern std::queue<_error> error_queue;
extern std::queue<_warning> warning_queue;


/*
 * Interface of lexer
 */
int lex_main(int argc, char** argv) {
#ifdef TEST_ON
	init_symbol_table("test_dummy", "test_dummy");
	test_lexer();
#else
	if (argc == 1) {
		std::cout << "Invalid parameter!" << std::endl;
		return 0;
	}
	if (argv[1][0] == '-') {
		switch(argv[1][1]) {
			case 'h':
				help_menu();
				break;
			case 'v':
				show_version();
				break;
			default:
				std::cout << "Unknown parameter, please check again" << std::endl << std::endl;
		}
	}else {
		init_symbol_table(argv[0], argv[1]);
		read_file();
	}
#endif /* end of TEST_ON */

#ifdef DUMP_TOKEN_STREAM
	dump_token_stream();
	POP_WARNING();
	POP_ERROR();
#endif /* end of DUMP_TOKEN_STREAM */
	/* printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count); */
	return 0;
}

/*
 * Read file and start to lex
 */
void read_file() {
	file.open(source_file.filename);
	EXPECT_TRUE(file.is_open());
	if (file.is_open()) {
		while (std::getline(file, cur_line)) {
			cur_line_info++;
			lex();
		}
	} else {
		std::cout << "Failed to open file! Please check your input!" << std::endl;
	}
}

/*
 * Initialize the symbol table
 */
void init_symbol_table(const char* filedir, const char* filename) {
	symbol_table.filedir = filedir;
	symbol_table.filename = filename;
	symbol_table.version = version;
	symbol_table.language = language_c;
	symbol_table.source_vector.push_back(source_file);
	source_file.filename = symbol_table.filename;
}


#define ISDIGIT(ch)         	((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     	((ch) >= '1' && (ch) <= '9')
#define ISDIGIT0(ch)			((ch) == '0')
#define ISDOT(ch)				((ch) == '.')
#define ISHEX(ch)				(ISDIGIT((ch)) || ((ch) >= 'a' && (ch) <= 'f') || ((ch) >= 'A' && (ch) <= 'F'))
#define ISOCT(ch)				((ch) >= '0' && (ch) <= '7')
#define ISWHITESPACE(ch)		((ch) == ' ')
#define ISLETTER(ch)			(((ch) >= 'a' && (ch) <= 'z') || ((ch >= 'A') && (ch) <= 'Z'))
#define ISUNDERSCORE(ch)		((ch) == '_')
#define ISIDENTIFIER(ch)		(ISDIGIT((ch)) || ISLETTER((ch)) || ISUNDERSCORE((ch)))
#define ISNOTEOF(ch)			((ch) != EOF)
#define ISNOTEOS(ch)			((ch) != '\0')	/* Is not end of string */
/* must consider the escape ' and " */
#define ISREAL1QUOTE(ch1, ch2)	((ch1) != '\\' && (ch2) == '\'')
#define ISREAL2QUOTE(ch1, ch2)	((ch1) != '\\' && (ch2) == '\"')


/*
 * Simple wrap for push token, used for operator token
 */
#define PUSH_TOKEN(type, name) \
	do {\
		token.set(idx, type, name);\
		source_file.push(token);\
	}while(0)
		
/*
 * Simple wrap for push token, used for other token
 */
#define PUSH_TOKEN_LITERAL(type, name) \
	do {\
		token.set(start, type, name);\
		source_file.push(token);\
	}while(0)
		
/*
 * Push error into the queue
 */
#define PUSH_ERROR(linenum, col, ERR_ID) \
	do {\
		_error e(ERR_ID, linenum, col);\
		error_queue.push(e);\
	}while(0)

/*
 * Push warning into the queue
 */
#define PUSH_WARNING(linenum, col, WARNING_ID) \
	do {\
		_warning w(WARNING_ID, linenum, col);\
		warning_queue.push(w);\
	}while(0)

/*
 * Represent the current token
 */
c_token token;
/*
 * If current line is one of multi-line comment?
 */
bool is_comment = false;

/*
 * Set the line number of token
 */
void init_token() {
	token.set_line(cur_line_info.linenum);
}

/* 
 * main function of lex 
 */
void lex() {
	init_token();
	for (size_t idx = 0; idx < cur_line.size();) {
		if (is_comment) {									/* If still comment, keep parsing it */
			parse_multi_line_comment(idx);
		} else if (ISWHITESPACE(cur_line[idx])) {					/* Trim space */
			PRINT("parse whitespace");
			trim_space(idx);
		} else if (ISDIGIT0(cur_line[idx])) {				/* Start with 0 */
			if (cur_line[idx + 1] == 'x' || cur_line[idx + 1] == 'X') { 				/* Hexadecimal */
				PRINT("parse hex number");
				idx += 2;									/* TODO */
				parse_num_hex(idx);
			} else if (ISDOT(cur_line[idx + 1])) {			/* decimal point */
				parse_num_decimal(idx);
			} else if (!ISDIGIT(cur_line[idx + 1])) {		/* 0 */
				PUSH_TOKEN(C_NUMBER, "0");
				idx++;
			} else { 										/* Start with 0, octal number */
				parse_num_oct(idx);
			}
		} else if (ISDIGIT1TO9(cur_line[idx])) { 			/* Decimal */
			PRINT("parse decimal number");
			parse_num_decimal(idx);
		} else if (ISLETTER(cur_line[idx]) || ISUNDERSCORE(cur_line[idx])) {				/* Identifier or keyword */
			PRINT("parse letter");
			parse_identifier(idx);
		} else { 											/* Operator or semicolon */
			PRINT("parse operator");
			switch(cur_line[idx]) {
				case '=':
					if (cur_line[idx + 1] == '=') { 			/* == */
						PUSH_TOKEN(C_EQ_EQ, "==");
						idx += 2;
					} else {									/* = */
						PUSH_TOKEN(C_EQ, "=");
						idx++;
					}
					break;
				case '\t':
					idx++;
					break;
				case ';':
					PUSH_TOKEN(C_SEMICOLON, ";");				/* ; */
					idx++;
					break;
				case '!':
					if (cur_line[idx + 1] == '=') {				/* != */
						PUSH_TOKEN(C_NOT_EQ, "!=");
						idx += 2;
					} else {									/* ! */
						PUSH_TOKEN(C_NOT, "!");
						idx++;
					}
					break;
				case '>':
					if (cur_line[idx + 1] == '>') {				/* >> or >>= */
						if (cur_line[idx + 2] == '=') {			/* >>= */
							PUSH_TOKEN(C_RSHIFT_EQ, ">>=");
							idx += 3;
						} else {								/* >> */
							PUSH_TOKEN(C_RSHIFT, ">>");
							idx += 2;
						}
					}else if (cur_line[idx + 1] == '=') {		/* >= */
						PUSH_TOKEN(C_GREATER_EQ, ">=");
						idx += 2;
					}else {										/* > */
						PUSH_TOKEN(C_GREATER, ">");
						idx++;
					}
					break;
				case '<':
					if (cur_line[idx + 1] == '<') {				/* << or <<= */
						if (cur_line[idx + 2] == '=') {			/* <<= */
							PUSH_TOKEN(C_LSHIFT_EQ, "<<=");
							idx += 3;
						} else {								/* << */
							PUSH_TOKEN(C_LSHIFT, "<<");
							idx += 2;
						}
					}else if (cur_line[idx + 1] == '=') {		/* <= */
						PUSH_TOKEN(C_LESS_EQ, "<=");
						idx += 2;
					}else {										/* < */
						PUSH_TOKEN(C_LESS, "<");
						idx++;
					}
					break;
				case '+':
					if (cur_line[idx + 1] == '+') {				/* ++ */
						PUSH_TOKEN(C_PLUS_PLUS, "++");
						idx += 2;
					} else if (cur_line[idx + 1] == '=') {		/* += */
						PUSH_TOKEN(C_PLUS_EQ, "+=");
						idx += 2;
					} else {									/* +  */
						PUSH_TOKEN(C_PLUS, "+");
						idx++;
					}
					break;
				case '-':
					if (cur_line[idx + 1] == '-') {				/* -- */
						PUSH_TOKEN(C_MINUS_MINUS, "--");
						idx += 2;
					} else if (cur_line[idx + 1] == '=') {		/* -= */
						PUSH_TOKEN(C_MINUS_EQ, "-=");
						idx += 2;
					} else if (cur_line[idx + 1] == '>') {		/* -> */
						PUSH_TOKEN(C_DEREF, "->");
						idx += 2;
					} else {									/* -  */
						PUSH_TOKEN(C_MINUS, "-");
						idx++;
					}
					break;
				case '*':
					if (cur_line[idx + 1] == '=') {				/* *= */
						PUSH_TOKEN(C_MULT_EQ, "*=");
						idx += 2;
					} else {									/* * */
						PUSH_TOKEN(C_MULT, "*");
						idx++;
					}
					break;
				case '/':
					if (cur_line[idx + 1] == '=') {				/* /= */
						PUSH_TOKEN(C_DIV_EQ, "/=");
						idx += 2;
					} else if (cur_line[idx + 1] == '/') {		/* //comment */
						PRINT("parse single line comment");
						idx += 2;
						parse_single_line_comment(idx);
					} else if (cur_line[idx + 1] == '*') {		/* multi-line comment */
						PRINT("parse multi-line comment");
						idx += 2;
						parse_multi_line_comment(idx);
					} else {									/* / */
						PUSH_TOKEN(C_DIV, "/");
						idx++;
					}
					break;
				case '%':
					if (cur_line[idx + 1] == '=') {				/* %= */
						PUSH_TOKEN(C_MOD_EQ, "%=");
						idx += 2;
					} else {									/* % */
						PUSH_TOKEN(C_MOD, "%");
						idx++;
					}
					break;
				case '&':
					if (cur_line[idx + 1] == '=') {				/* &= */
						PUSH_TOKEN(C_AND_EQ, "&=");
						idx += 2;
					} else if (cur_line[idx + 1] == '&') {		/* && */
						PUSH_TOKEN(C_AND_AND, "&&");
						idx += 2;
					} else {									/* & */
						PUSH_TOKEN(C_AND, "&");
						idx++;
					}
					break;
				case '|':
					if (cur_line[idx + 1] == '|') {				/* || */
						PUSH_TOKEN(C_OR_OR, "||");
						idx += 2;
					} else if (cur_line[idx + 1] == '=') {		/* |= */
						PUSH_TOKEN(C_OR_EQ, "|=");
						idx += 2;
					} else {									/* | */
						PUSH_TOKEN(C_OR, "|");
						idx++;
					}
					break;
				case '^':
					if (cur_line[idx + 1] == '=') {				/* ^= */
						PUSH_TOKEN(C_XOR_EQ, "^=");
						idx += 2;
					} else {									/* ^ */	
						PUSH_TOKEN(C_XOR, "^");
						idx++;
					}
					break;
				case '~':										/* ~ */
					PUSH_TOKEN(C_COMPL, "~");
					idx++;
					break;
				case '?':										/* ? */
					PUSH_TOKEN(C_QUERY, "?");
					idx++;
					break;
				case ':':										
					if (cur_line[idx + 1] == ':') {				/* :: */
						PUSH_TOKEN(C_SCOPE, "::");
						idx += 2;
					} else {									/* : */
						PUSH_TOKEN(C_COLON, ":");
						idx++;
					}
					break;
				case ',':										/* , */
					PUSH_TOKEN(C_COMMA, ",");
					idx++;
					break;
				case '(':										/* ( */
					PUSH_TOKEN(C_OPEN_PAREN, "(");
					idx++;
					break;
				case ')':										/* ) */
					PUSH_TOKEN(C_CLOSE_PAREN, ")");
					idx++;
					break;
				case '[':										/* [ */
					PUSH_TOKEN(C_OPEN_SQUARE, "[");
					idx++;
					break;
				case ']':										/* ] */
					PUSH_TOKEN(C_CLOSE_SQUARE, "]");
					idx++;
					break;
				case '{':										/* { */
					PUSH_TOKEN(C_OPEN_BRACE, "{");		
					idx++;
					break;
				case '}':										/* } */
					PUSH_TOKEN(C_CLOSE_BRACE, "}");
					idx++;
					break;
				case '.':										/* . */
					PUSH_TOKEN(C_DOT, ".");
					idx++;
					break;
				case '\'':										/* 'char' */
					idx++;
					parse_char(idx);
					break;
				case '\"':										/* "string" */
					idx++;
					parse_string(idx);
					break;
				default:
					PUSH_ERROR(cur_line_info.linenum, idx, UNKNOWN_TYPE);
					idx++;
			}
		}
	}
}



void trim_space(size_t& idx) {
	while (cur_line[idx] == ' ' && ISNOTEOF(cur_line[idx])) {
		idx++;
	}
}
void parse_num_decimal(size_t& idx) {
	size_t start = idx;
	bool dot_flag = false;
	while (ISDIGIT(cur_line[idx]) || ISDOT(cur_line[idx])) {		/* While is digit */
		if (ISDOT(cur_line[idx])) {									/* If meet a dot */
			if (dot_flag) {											/* Already has a dot before */
				PUSH_ERROR(cur_line_info.linenum, start, TOO_MANY_DECIMAL_POINTS);
				break;
			} else {
				dot_flag = true;									/* Meet a dot in the first time */
			}
		}
		idx++;
	}
	PUSH_TOKEN_LITERAL(C_NUMBER, cur_line.substr(start, idx - start));
}

void parse_num_hex(size_t& idx) {
	size_t start = idx;
	while (ISHEX(cur_line[idx])) {
		idx++;
	}
	PUSH_TOKEN_LITERAL(C_NUMBER, "0x" + cur_line.substr(start, idx - start));
}

void parse_num_oct(size_t& idx) {
	size_t start = idx;
	bool not_pushed_flag = true; 										/* if it has not been pushed */
	while (ISDIGIT(cur_line[idx])) {
		if (not_pushed_flag && !ISOCT(cur_line[idx])) {					/* number 8 and 9 is invalid for octal */
			PUSH_ERROR(cur_line_info.linenum, start, INVALID_OCTAL_NUMBER);
			not_pushed_flag = false;
		}
		idx++;
	}
	PUSH_TOKEN_LITERAL(C_NUMBER, cur_line.substr(start, idx - start));
}

void parse_identifier(size_t& idx) {
	size_t start = idx;
	while (ISIDENTIFIER(cur_line[idx])) {
		idx++;
	}
	/* If the identifier is too long, push warning, and take the valid part */
	if (idx - start > LONGEST_IDENTIFIER_LENGTH) {	
		PUSH_WARNING(cur_line_info.linenum, start, TOO_LONG_IDENTIFIER);
		PUSH_TOKEN_LITERAL(C_NAME, cur_line.substr(start, LONGEST_IDENTIFIER_LENGTH));
	} else {
		PUSH_TOKEN_LITERAL(C_NAME, cur_line.substr(start, idx - start));
	}
	
}

void parse_char(size_t& idx) {					/* The first ' has been skipped */
	size_t start = idx;
	while (ISNOTEOS(cur_line[idx]) && !ISREAL1QUOTE(cur_line[idx - 1], cur_line[idx])) {			/* How far will it meet ' ? */
		idx++;
	}
	if (idx - start > 1) {						/* Only 1 character can exist bewteen '' */
		PUSH_WARNING(cur_line_info.linenum, start, CHAR_TOO_LONG);
	}
	
	if (idx == cur_line.size()) {
		PUSH_ERROR(cur_line_info.linenum, start, MISSING_TERMINATING_1_QUOTE);
	}
	PUSH_TOKEN_LITERAL(C_CHAR, cur_line.substr(start, 1));
	idx++;										/* Skip the final ' */
}
void parse_string(size_t& idx) {				/* The first " has been skipped */
	size_t start = idx;
	while (ISNOTEOS(cur_line[idx]) && !ISREAL2QUOTE(cur_line[idx - 1], cur_line[idx])) {
		idx++;
	}
	if (idx == cur_line.size()) {
		PUSH_ERROR(cur_line_info.linenum, start, MISSING_TERMINATING_2_QUOTE);
	}
	PUSH_TOKEN_LITERAL(C_STRING, cur_line.substr(start, idx - start));
	idx++;										/* Skip the final " */
}
void parse_single_line_comment(size_t& idx) {	/* the first // has been skipped */
	while (idx < cur_line.size())				/* just skip to the end of the line */
		idx++;
}
void parse_multi_line_comment(size_t& idx) {
	if (is_comment) {							/* the status is in multi-line comment */
		while (1) {
			if ((idx + 1 < cur_line.size()) && cur_line[idx] == '*' && cur_line[idx + 1] == '/') {
				is_comment = false;
				idx += 2;
				break;
			} else if (idx >= cur_line.size()) {
				break;
			}
			idx++;
		}
	} else {									/* just start the multi-line comment */
		is_comment = true;
	}
}








