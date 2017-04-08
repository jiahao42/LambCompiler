#include "lex_config.h"
#include "lex.h"
#include "util.h"
#include "test.h"

extern const std::string version;
symbol_root symbol_table;
std::ifstream file;
std::string cur_line;
line cur_line_info;
source source_file;
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
	
	return 0;
}

/*
 * Read file and start to lex
 */
void read_file() {
	source_file.name = symbol_table.filename;
	file.open(source_file.name);
	EXPECT_TRUE(file.is_open());
	if (file.is_open()) {
		while (std::getline(file, cur_line)) {
			cur_line_info++;
			lex();
			if (error_code == NO_ERROR) {
				ERROR(error_code)
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
}