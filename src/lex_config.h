#ifndef LEX_CONFIG_H_
#define LEX_CONFIG_H_

#define DEBUG

#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <vector>
#include "symseg.h"
#include "token.h"

extern std::ifstream file;
extern line cur_line;
extern source source_file;
extern symbol_root symbol_table;
extern int line_count;
extern int error_code;

#define SYMBOL_TABLE_SIZE 1000

#define LONGEST_IDENTIFIER_LENGTH 32


#endif /* end of LEX_CONFIG_H_ */