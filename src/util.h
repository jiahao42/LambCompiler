//LambLexer
//by James 2017/04/06

#ifndef LAMB_COMPILER_UTIL_H_
#define LAMB_COMPILER_UTIL_H_

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




#endif /* end of LAMB_COMPILER_UTIL_H_ */