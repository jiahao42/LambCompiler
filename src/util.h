#ifndef LAMBLEXER_UTIL_H_
#define LAMBLEXER_UTIL_H_

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

/*
 * Output token stream to console
 */
void dump_token_stream();


#endif /* end of LAMBLEXER_UTIL_H_ */