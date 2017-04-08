#include "lex_config.h"
#include "lex.h"

#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')
#define ISDIGIT0(ch)		((ch) == '0'))
#define ISWHITESPACE(ch)	((ch) == ' ')
#define ISLETTER(ch)		(((ch) >= 'a' && (ch) <= 'z') || ((ch >= 'A') && (ch) <= 'Z'))
#define ERROR(ERR_ID) std::cout << "line: " << cur_line_info.linenum << " error: " << error_string[ERR_ID] << std::endl

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
		if (ISWHITESPACE(cur_line[idx]) {
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
		} else if (ISLETTER(cur_line[idx]) {				/* identifier or keyword */
			parse_identifier(idx);
		} else { 											/* operator or semicolon */
			switch(cur_line[idx]) {
				case '=':
					if (cur_line[idx + 1] == '=') { 			/* == */
						c_token tmp(cur_line_info.linenum, idx, C_EQ_EQ, "==");
						source_file.c_token_vector.push_back(tmp);
						idx += 2;
					} else {								/* = */
						c_token tmp(cur_line_info.linenum, idx, C_EQ, "=");
						source_file.c_token_vector.push_back(tmp);
						idx++;
					}
					break;
				case ';':
					c_token(cur_line_info.linenum, idx, C_SEMICOLON, ";");
					source_file.c_token_vector.push_back(tmp);
					idx++;
					break;
				default:
					c_token(cur_line_info.linenum, idx, C_OTHER, cur_line[idx]);
					source_file.c_token_vector.push_back(tmp);
					idx++;
			}
		}
	}
}



void trim_space(size_t& idx) {
	while (cur_line[idx] == ' ' && idx < cur_line.size()) {
		i++;
	}
}
void parse_num(size_t& idx) {
	
}
void parse_identifier(size_t& idx) {
	
}










