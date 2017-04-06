# LambLexer
# by James 2017/04/06

CXX = g++
CXXFLAGS = -g -Wall -O2 -std=c++11
BIN = bin
SRC = src
OBJ = obj
EXE = $(BIN)/lexer.exe

LEX_CONFIG_H = $(SRC)/lex_config.h
LEX_H = $(SRC)/lex.h
UTIL_H = $(SRC)/util.h
TOKEN_H = $(SRC)/token.h

LEX_CPP = $(SRC)/lex.cpp
UTIL_CPP = $(SRC)/util.cpp
TOKEN_CPP = $(SRC)/token.cpp
MAIN_CPP = $(SRC)/main.cpp

OBJS = main.o util.o token.o lex.o

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)/lex.o $(OBJ)/token.o $(OBJ)/util.o $(OBJ)/main.o
main.o: $(LEX_CONFIG_H) $(LEX_H) $(UTIL_H) $(TOKEN_H)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/main.o -c $(MAIN_CPP)
lex.o: $(LEX_CONFIG_H) $(LEX_H) $(LEX_CPP)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/lex.o -c $(LEX_CPP)
util.o: $(LEX_CONFIG_H) $(UTIL_H) $(UTIL_CPP)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/util.o -c $(UTIL_CPP)
token.o: $(LEX_CONFIG_H) $(TOKEN_H) $(TOKEN_CPP)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/token.o -c $(TOKEN_CPP)



clean:
	rm $(OBJ)/*.o
