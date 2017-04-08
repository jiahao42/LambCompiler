#ifndef LAMBLEXER_UTIL_H_
#define LAMBLEXER_UTIL_H_

#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')
#define ISLETTER(ch)		(((ch) >= 'a' && (ch) <= 'z') || ((ch >= 'A') && (ch) <= 'Z'))
#define ERROR(ERR_ID) std::cout << "line: " << cur_line_info.linenum << " error: " << error_string[ERR_ID] << std::endl

/*
 * ELFHash, used for access varible in Symbol Table faster
 */
unsigned int ELFHash(std::string str); 

/*
 * Help menu
 */
void help_menu();

/*
 * Show version
 */
void show_version();

#endif /* end of LAMBLEXER_UTIL_H_ */