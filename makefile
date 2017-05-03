# LambLexer
# by James 2017/04/06

CXX = g++
CXXFLAGS = -g -Wall -O2 -std=c++11
BIN = bin
SRC = src
OBJ = obj
COMPILER = $(BIN)/compiler

MODULES=parser compiler test token lex util main
COMPILER_OBJS=$(MODULES:%=$(OBJ)/%.o)

$(OBJ)/%.o: $(SRC)/%.cpp
	@test -d $(OBJ) || mkdir $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

compiler: $(COMPILER_OBJS)
	@test -d $(OBJ) || mkdir $(BIN)
	$(CXX) $(CXXFLAGS) -o $(COMPILER) $(COMPILER_OBJS)

clean:
	rm $(OBJ)/*.o
