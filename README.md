# LambCompiler v0.0.4

**This is a simple compiler for a subset of ANSI C. By now, it can generate the pseudo-code without type-checking.**

### 1. Before Compilation

See `config.h`, make sure it is the desired configuration. The default configuration is `Test Mode`, which means it use the previously defined test data.

### 2. How to compile

Make sure you have installed GNU Make

* Run `make` or `make compiler` to compile the compiler, the executable file is under `LambCompiler/bin`
* Run `make lexer` to compile the lexer, the executable file is under `LambCompiler/bin`

### 3. Usage

#### 3.1 Normal Mode
* ./compiler [filename]
* ./compiler -v
* ./compiler -h

#### 3.2 Test Mode (no parameter needed)
* ./compiler

### 4. Sample

![](https://raw.githubusercontent.com/Jameeeees/LambCompiler/master/doc/output.PNG)

