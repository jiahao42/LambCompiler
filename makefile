# LambLexer
# by James 2017/04/06

CXX = g++
CXXFLAGS = -g -Wall -O2 -std=c++11
BIN = bin
SRC = src
OBJ = obj
EXE = $(BIN)/lexer

LEX_CONFIG_H = $(SRC)/lex_config.h
LEX_H = $(SRC)/lex.h
UTIL_H = $(SRC)/util.h
TOKEN_H = $(SRC)/token.h
TEST_H = $(SRC)/test.h
ERROR_H = $(SRC)/error.h
SYMSEG_H = $(SRC)/symseg.h

LEX_CPP = $(SRC)/lex.cpp
UTIL_CPP = $(SRC)/util.cpp
TOKEN_CPP = $(SRC)/token.cpp
MAIN_CPP = $(SRC)/main.cpp

OBJS = util.o token.o lex.o main.o

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)/lex.o $(OBJ)/token.o $(OBJ)/util.o $(OBJ)/main.o
main.o:
	$(CXX) $(CXXFLAGS) -o $(OBJ)/main.o -c $(MAIN_CPP)
lex.o: 
	$(CXX) $(CXXFLAGS) -o $(OBJ)/lex.o -c $(LEX_CPP)
util.o: 
	$(CXX) $(CXXFLAGS) -o $(OBJ)/util.o -c $(UTIL_CPP)
token.o: 
	$(CXX) $(CXXFLAGS) -o $(OBJ)/token.o -c $(TOKEN_CPP)



clean:
	rm $(OBJ)/*.o
