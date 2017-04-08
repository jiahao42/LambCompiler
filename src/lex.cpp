#include "lex_config.h"
#include "token.h"
#include "symseg.h"
#include "error.h"
#include "test.h"
#include "lex.h"


#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')
#define ISDIGIT0(ch)		((ch) == '0'))
#define ISWHITESPACE(ch)	((ch) == ' ')
#define ISLETTER(ch)		(((ch) >= 'a' && (ch) <= 'z') || ((ch >= 'A') && (ch) <= 'Z'))

extern std::string cur_line;
extern int error_code;
extern line cur_line_info;
extern source source_file;


void trim_space(size_t&);
void parse_num(size_t&);
void parse_identifier(size_t&);

/* 
 * main function of lex 
 */
void lex() {
	for (size_t idx = 0; idx < cur_line.size(); idx++) {
		c_token tmp(cur_line_info.linenum);
		if (ISWHITESPACE(cur_line[idx])) {					/* trim space */
			PRINT("parse whitespace");
			trim_space(idx);
		} else if (ISDIGIT0(cur_line[idx]) {				/* start with 0 */
			PRINT("parse number");
			if (cur_line[idx + 1] == 'x') { 				/* hexadecimal */
				idx++;										/* TODO */
				parse_num(idx);
			} else if (!ISDIGIT(cur_line[idx + 1])) {		/* 0 */
				tmp.set(idx, C_NUMBER, "0");
				source_file.push(tmp);
				idx++;
			} else { 										/* start with 0 but not hexadecimal */
				ERROR(NON_HEX_NUMBER_START_WITH_ZERO, idx);
			}
		} else if (ISDIGIT1TO9(cur_line[idx])) { 			/* decimal */
			parse_num(idx);
		} else if (ISLETTER(cur_line[idx])) {				/* identifier or keyword */
			PRINT("parse letter");
			parse_identifier(idx);
		} else { 											/* operator or semicolon */
			PRINT("parse operator");
			switch(cur_line[idx]) {
				case '=':
					if (cur_line[idx + 1] == '=') { 			/* == */
						tmp.set(idx, C_EQ_EQ, "==");
						source_file.push(tmp);
						idx += 2;
					} else {									/* = */
						tmp.set(idx, C_EQ, "=");
						source_file.push(tmp);
						idx++;
					}
					break;
				case ';':
					tmp.set(idx, C_SEMICOLON, ";");				/* ; */
					source_file.push(tmp);
					idx++;
					break;
				case '!':
					if (cur_line[idx + 1] == '=') {				/* != */
						tmp.set(idx, C_NOT_EQ, "!=");
						source_file.push(tmp);
						idx += 2;
					} else {									/* ! */
						tmp.set(idx, C_NOT, "!");
						source_file.push(tmp);
						idx++;
					}
					break;
				case '>':
					if (cur_line[idx + 1] == '>') {				/* >> or >>= */
						if (cur_line[idx + 2] == '=') {			/* >>= */
							tmp.set(idx, C_RSHIFT_EQ, ">>=");
							source_file.push(tmp);
							idx += 3;
						} else {								/* >> */
							tmp.set(idx, C_RSHIFT, ">>");
							source_file.push(tmp);
							idx += 2;
						}
					}else if (cur_line[idx + 1] == '=') {		/* >= */
						tmp.set(idx, C_GREATER_EQ, ">=");
						source_file.push(tmp);
						idx += 2;
					}else {										/* > */
						tmp.set(idx, C_GREATER, ">");
						source_file.push(tmp);
						idx++;
					}
					break;
				case '<':
					if (cur_line[idx + 1] == '<') {				/* << or <<= */
						if (cur_line[idx + 2] == '=') {			/* <<= */
							tmp.set(idx, C_LSHIFT_EQ, "<<=");
							source_file.push(tmp);
							idx += 3;
						} else {								/* << */
							tmp.set(idx, C_LSHIFT_EQ, "<<");
							source_file.push(tmp);
							idx += 2;
						}
					}else if (cur_line[idx + 1] == '=') {		/* <= */
						tmp.set(idx, C_LESS_EQ, "<=");
						source_file.push(tmp);
						idx += 2;
					}else {										/* < */
						tmp.set(idx, C_LESS, "<");
						source_file.push(tmp);
						idx++;
					}
					break;
				case '+':
					if (cur_line[idx + 1] == '+') {				/* ++ */
						tmp.set(idx, C_PLUS_PLUS, "++");
						source_file.push(tmp);
						idx += 2;
					} else if (cur_line[idx + 1] == '=') {		/* += */
						tmp.set(idx, C_PLUS_EQ, "+=");
						source_file.push(tmp);
						idx += 2;
					} else {									/* +  */
						tmp.set(idx, C_PLUS, "+");
						source_file.push(tmp);
						idx++;
					}
					break;
				case '-':
					if (cur_line[idx + 1] == '-') {				/* -- */
						tmp.set(idx, C_MINUS_MINUS, "--");
						source_file.push(tmp);
						idx += 2;
					} else if (cur_line[idx + 1] == '=') {		/* -= */
						tmp.set(idx, C_MINUS_EQ, "-=");
						source_file.push(tmp);
						idx += 2;
					} else if (cur_line[idx + 1] == '>') {		/* -> */
						tmp.set(idx, C_DEREF, "->");
						source_file.push(tmp);
						idx += 2;
					} else {									/* -  */
						tmp.set(idx, C_MINUS, "-");
						source_file.push(tmp);
						idx++;
					}
					break;
				case '*':
					if (cur_line[idx + 1] == '=') {				/* *= */
						tmp.set(idx, C_MULT_EQ, "*=");
						source_file.push(tmp);
						idx += 2;
					} else {									/* * */
						tmp.set(idx, C_MULT, "*");
						source_file.push(tmp);
						idx++;
					}
					break;
				default:
					ERROR(UNKNOWN_TYPE, idx);
					idx++;
			}
		}
	}
}



void trim_space(size_t& idx) {
	while (cur_line[idx] == ' ' && idx < cur_line.size()) {
		idx++;
	}
}
void parse_num(size_t& idx) {
	
}
void parse_identifier(size_t& idx) {
	
}










