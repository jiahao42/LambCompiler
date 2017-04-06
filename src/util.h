#ifndef UTIL_H_
#define UTIL_H_

#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')

static unsigned int ELFHash(std::string str); 

#endif