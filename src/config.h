//LambLexer
//by James 2017/04/06

#ifndef LAMB_COMPILER_CONFIG_H_
#define LAMB_COMPILER_CONFIG_H_


#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iomanip>
#include <map>

/*
 * The top test switch
 */
#define TEST_ON
//#undef TEST_ON

/*
 * Output token stream to console or not, see lex.h
 */
#define DUMP_TOKEN_STREAM
#undef DUMP_TOKEN_STREAM

/*
 * Print the log
 */
#define PRINT_LOG
#undef PRINT_LOG

/* 
 * This macro is for DEBUG message
 */
#ifdef PRINT_LOG
#define PRINT(msg) std::cout << "msg: " << msg << std::endl;
#define PRINT_TOKEN(token) std::cout << "token: " << token << std::endl;
#else
#define PRINT(msg) do{}while(0)
#define PRINT_TOKEN(token) do{}while(0)
#endif


/*
 * The length limit of identifier
 */
#define LONGEST_IDENTIFIER_LENGTH 32

/*
 * Version info
 */
const std::string version = "0.4";


#endif /* end of LAMB_COMPILER_CONFIG_H_ */
