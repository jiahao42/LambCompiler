//LambLexer
//by James 2017/04/06

#ifndef LAMBLEXER_LEX_CONFIG_H_
#define LAMBLEXER_LEX_CONFIG_H_


#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_map>

/*
 * The test switch, see test.cpp
 */
#define TEST_ON

/*
 * Output token stream to console or not, see util.h
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
#else
#define PRINT(msg) do{}while(0)
#endif

/*
 * If show keyword judgement when dumping token stream to console
 */
#define SHOW_KEYWORD_FILTER

/*
 * The length limit of identifier
 */
#define LONGEST_IDENTIFIER_LENGTH 32

/*
 * Version info
 */
const std::string version = "0.0.1";


#endif /* end of LAMBLEXER_LEX_CONFIG_H_ */