#ifndef LAMBLEXER_LEX_CONFIG_H_
#define LAMBLEXER_LEX_CONFIG_H_

#define DEBUG

#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <vector>
#include <unordered_map>

/*
 * Output token stream to console or not
 */
#define DUMP_TOKEN_STREAM

/*
 * The length limit of identifier
 */
#define LONGEST_IDENTIFIER_LENGTH 32

/*
 * Version info
 */
const std::string version = "0.0.1";





#endif /* end of LAMBLEXER_LEX_CONFIG_H_ */