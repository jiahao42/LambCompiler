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

void trim_space(size_t&);
void parse_num(size_t&);
void parse_identifier(size_t&);

/* 
 * main function of lex 
 */
void lex() {
	for (size_t idx = 0; idx < cur_line.length(); idx++) {
		if (ISWHITESPACE(cur_line[idx]) {
			trim_space(idx);
		} else if (ISDIGIT0(cur_line[idx]) {
			if (cur_line[idx + 1] == 'x') { // hexadecimal
				idx++;
				parse_num(idx);
			} else { // start with 0 but not hexadecimal
				ERROR(NON_HEX_NUMBER_START_WITH_ZERO);
			}
		} else if (ISDIGIT1TO9(cur_line[idx])) { // decimal
			parse_num(idx);
		} else if (ISLETTER(cur_line[idx]) { // identifier or keyword
			parse_identifier(idx);
		}
	}
}














