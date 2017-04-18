//LambLexer
//by James 2017/04/06

#ifndef LAMBLEXER_LEX_H_
#define LAMBLEXER_LEX_H_

/*
 * Interface of the lexer
 */
int lex_main(int argc, char** argv);

/*
 * Read file and start to lex
 */
void read_file();

/*
 * Initialize the symbol table
 */
void init_symbol_table(const char* filedir, const char* filename);

/*
 * Set the line number of token
 */
void init_token();

/* 
 * main function of lex 
 */
void lex();

/*
 * Trim the spaces
 */
void trim_space(size_t&);

/* 
 * Parse decimal number
 */
void parse_num_decimal(size_t&);

/*
 * Parse hexadecimal number
 */
void parse_num_hex(size_t&);

/*
 * Parse octal number
 */
void parse_num_oct(size_t&);

/*
 * Parse identifier, start with letter or underscore
 */
void parse_identifier(size_t&);

/*
 * Parse character, start with ', also end with ', be careful with escape '
 */
void parse_char(size_t&);

/*
 * Parse string, start with ", also end with ", be careful with escape "
 */
void parse_string(size_t&);

/* 
 * Parse single line commeng, start with // 
 */
void parse_single_line_comment(size_t&);

/* 
 * Parse multi-line comment, start with *\/, also end with *\/
 */ 
void parse_multi_line_comment(size_t&);

#endif /* end of LAMBLEXER_LEX_H_ */