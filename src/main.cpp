#include "lex_config.h"
#include "lex.h"
#include "token.h"
#include "util.h"

/*
 * Used for Simple Test Framework
 */
static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Invalid parameter!" << std::endl;
		return 0;
	}
	/*
	 * Help menu
	 */
	if (strcmp(argv[1],"-h") == 0) {
		std::cout << "This is help menu." << std::endl;
		return 0;
	}
	
	std::ifstream source_file;
	std::string line;
	int line_count = 0;
	int error_code = NO_ERROR;
	
	source_file.open(argv[1]);
	EXPECT_EQ_STRING("sample", argv[1], 6);

	if (source_file.is_open()) {
		while (std::getline(source_file, line)) {
			line_count++;
			lex();
			if (error_code != NO_ERROR) {
				std::cout << "line: " << line_count << " error: " << error_string[error_code] << std::endl;
			}
		}
	} else {
		std::cout << "Failed to open file! Please check your input!" << std::endl;
	}
	return 0;
}