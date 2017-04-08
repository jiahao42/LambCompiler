#ifndef LAMBLEXER_LEX_CONFIG_H_
#define LAMBLEXER_LEX_CONFIG_H_

#define DEBUG

#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <vector>
#include "error.h"
#include "symseg.h"
#include "token.h"

/*
 * Current file
 */
extern std::ifstream file;
/*
 * Information of current line, including line number and line address
 * See symseg.h
 */
extern line cur_line_info;
/*
 * Literally current line
 */
extern std::string cur_line;
/*
 * Stand for source file, including filename and lines' info
 * See symseg.h
 */
extern source source_file;
/*
 * Symbol table, see symseg.harderr
 */
extern symbol_root symbol_table;
/*
 * Correspond with error_string, see token.h
 */ 
extern int error_code;
/*
 * Version info
 */
const std::string version = "0.0.1";


/*
 * The length limit of identifier
 */
#define LONGEST_IDENTIFIER_LENGTH 32


#endif /* end of LAMBLEXER_LEX_CONFIG_H_ */