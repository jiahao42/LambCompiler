#include "lex_config.h"
#include "lex.h"
#include "token.h"
#include "util.h"

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Invalid parameter!" << std::endl;
		return 0;
	}
	if (strcmp(argv[1],"-h") == 0) {
		std::cout << "This is help menu." << std::endl;
		return 0;
	}
	
	text.open(argv[1]);
	if (text.is_open()) {
		while (std::getline(text, line)) {
			line_count++;
			lex();
			if (!error_code) {
				std::cout << "line: " << line_count << "error: " << error_string[error_code] << std::endl;
			}
		}
	} else {
		std::cout << "Failed to open file! Please check your input!" << std::endl;
	}
	return 0;
}