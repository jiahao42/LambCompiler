# LambCompiler v0.0.3

This is a simple compiler for a subset of ANSI C.

### 1. Before Compilation
See `lex_config.h`, make sure it is the desired configuration. The default configuration is `Test Mode`, which means it use the previously defined test data.

### 2. How to compile
Make sure you have installed GNU Make

* Run `make lexer` to compile the lexer, the executable file is under `LambCompiler/bin`
* Run `make compiler` to compile the compiler, the executable file is under `LambCompiler/bin`

### 3. Usage

#### 3.1 Normal Mode
* ./compiler [filename]
* ./compiler -v
* ./compiler -h

#### 3.2 Test Mode (no parameter needed)
* ./compiler


