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
		c_token tmp;
		if (ISWHITESPACE(cur_line[idx])) {
			trim_space(idx);
		} else if (ISDIGIT0(cur_line[idx]) {
			if (cur_line[idx + 1] == 'x') { 				/* hexadecimal */
				idx++;
				parse_num(idx);
			} else { 										/* start with 0 but not hexadecimal */
				ERROR(NON_HEX_NUMBER_START_WITH_ZERO);
			}
		} else if (ISDIGIT1TO9(cur_line[idx])) { 			/* decimal */
			parse_num(idx);
		} else if (ISLETTER(cur_line[idx])) {				/* identifier or keyword */
			parse_identifier(idx);
		} else { 											/* operator or semicolon */
			switch(cur_line[idx]) {
				case '=':
					if (cur_line[idx + 1] == '=') { 			/* == */
						tmp.set(cur_line_info.linenum, idx, C_EQ_EQ, "==");
						source_file.c_token_vector.push_back(tmp);
						idx += 2;
					} else {								/* = */
						tmp.set(cur_line_info.linenum, idx, C_EQ, "=");
						source_file.c_token_vector.push_back(tmp);
						idx++;
					}
					break;
				case ';':
					tmp.set(cur_line_info.linenum, idx, C_SEMICOLON, ";");
					source_file.c_token_vector.push_back(tmp);
					idx++;
					break;
				default:
					ERROR(UNKNOWN_TYPE);
					idx++;
					break;
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










