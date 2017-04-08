#include "lex_config.h"
#include "lex.h"
#include "symseg.h"
#include "token.h"
#include "util.h"
#include "error.h"
#include "test.h"

extern const std::string version;
/*
 * Symbol table, see symseg.harderr
 */
symbol_root symbol_table;
/*
 * Current file
 */
std::ifstream file;
/*
 * Literally current line
 */
std::string cur_line;
/*
 * Information of current line, including line number and line address
 * See symseg.h
 */
line cur_line_info;
/*
 * Stand for source file, including filename and lines' info
 * See symseg.h
 */
source source_file;
/*
 * Correspond with error_string, see token.h
 */ 
int error_code = NO_ERROR;

void read_file();
void init_symbol_table(const char*, const char*);

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Invalid parameter!" << std::endl;
		return 0;
	}
	if (argv[1][0] == '-') {
		switch(argv[1][1]) {
			case 'h':
			   /*
				* Help menu
				*/
				help_menu();
				break;
			case 'v':
			   /*
				* Show version
				*/
				show_version();
				break;
			default:
				std::cout << "Unknown parameter, please check again" << std::endl << std::endl;
		}
	}else {
		init_symbol_table(argv[0], argv[1]);
		read_file();
	}
#ifdef DUMP_TOKEN_STREAM
	void dump_token_stream();
#endif
	return 0;
}

/*
 * Read file and start to lex
 */
void read_file() {
	source_file.filename = symbol_table.filename;
	file.open(source_file.filename);
	EXPECT_TRUE(file.is_open());
	if (file.is_open()) {
		while (std::getline(file, cur_line)) {
			cur_line_info++;
			lex();
			if (error_code) {
				ERROR(error_code);
			}
		}
	} else {
		std::cout << "Failed to open file! Please check your input!" << std::endl;
	}
}

/*
 * Initialize the symbol table
 */
void init_symbol_table(const char* filedir, const char* filename) {
	symbol_table.filedir = filedir;
	symbol_table.filename = filename;
	symbol_table.version = version;
	symbol_table.language = language_c;
	symbol_table.source_vector.push_back(source_file);
}