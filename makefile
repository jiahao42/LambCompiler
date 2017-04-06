# LambLexer
# by James 2017/04/06

CXX = g++
CXXFLAGS = -g -Wall -O2 -std=c++11
BIN = bin
SRC = src
OBJ = obj
EXE = $(BIN)lexer.exe






clean:
	rm $(OBJ)\*.o
	rm $(BIN)\*.exe
