#include "lex_config.h"
#include "lex.h"
#include "util.h"
#include "test.h"

symbol_root symbol_table;
std::ifstream file;
std::string temp;
line cur_line;
source source_file;
int error_code = NO_ERROR;

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Invalid parameter!" << std::endl;
		return 0;
	}
   /*
	* Help menu
	*/
	if (strcmp(argv[1],"-h") == 0) {
		help_menu();
		return 0;
	}
   /*
	* Show version
	*/
	if (strcmp(argv[1], "-v") == 0) {
		show_version();
		return 0;
	}
	
	source_file.name = argv[1];
	file.open(argv[1]);
	EXPECT_TRUE(file.is_open());
	if (file.is_open()) {
		while (std::getline(file, temp)) {
			cur_line++;
			lex();
			if (error_code != NO_ERROR) {
				std::cout << "line: " << cur_line.linenum << " error: " << error_string[error_code] << std::endl;
			}
		}
	} else {
		std::cout << "Failed to open file! Please check your input!" << std::endl;
	}
	return 0;
}