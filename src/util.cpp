//LambLexer
//by James 2017/04/06

#include "lex_config.h"
#include "token.h"
#include "symseg.h"
#include "test.h"

extern symbol_root symbol_table;
extern const std::string version;
extern source source_file;
extern std::unordered_map<std::string, enum rid> keyword;

/*
 * ELFHash, used for access varible in Symbol Table faster
 */
unsigned int ELFHash(std::string str) {
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;
	unsigned int len = str.length();

	for (i = 0; i < len; i++)
	{
		hash = (hash << 4) + (str[i]);
		if ((x = hash & 0xF0000000) != 0)
		{
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}
	return hash;
}

/*
 * Help menu
 */
void help_menu() {
	std::cout << "This is the help menu" << std::endl;
	std::cout << "LambLexer, Version: " << version << std::endl << std::endl;;
}

/*
 * Show version
 */
void show_version() {
	std::cout << "LambLexer, Version: " << version << std::endl << std::endl;;
}


/*
 * Output token stream to console
 */
void dump_token_stream() {
#ifndef SHOW_KEYWORD_FILTER
	for (c_token c : source_file.c_token_vector) {
		std::cout << source_file.filename << c << std::endl;
	}
#else
	for (c_token c : source_file.c_token_vector) {
		auto it = keyword.find(c.name);
		if (keyword.end() == it)
			std::cout << source_file.filename << c << std::endl;
		else
			std::cout << source_file.filename << c << " [keyword]" << std::endl;
	}
#endif
}
















