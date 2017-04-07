#ifndef UTIL_H_
#define UTIL_H_

#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')
#define ISLETTER(ch)		(((ch) >= 'a' && (ch) <= 'z') || ((ch >= 'A') && (ch) <= 'Z'))

/*
 * ELFHash, used for access varible in Symbol Table faster
 */
unsigned int ELFHash(std::string str); 

#endif