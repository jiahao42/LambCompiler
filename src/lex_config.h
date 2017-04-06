#ifndef LEX_CONFIG_H_
#define LEX_CONFIG_H_

#include <iostream>
#include <cstring>
#include <fstream>
#include <assert.h>
#include <cstdio>

#define NDEBUG

static std::ifstream text;
static std::string line;
static int line_count;
static int error_code;

#endif