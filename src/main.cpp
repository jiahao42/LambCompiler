#include "lex_config.h"
#include "lex.h"
#include "util.h"

/*
 * Used for Simple Test Framework
 */
static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

/*
 * Simple Test Framework
 */
#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")
#define EXPECT_EQ_STRING(expect, actual, alength) \
    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength + 1) == 0, expect, actual, "%s")
#define EXPECT_TRUE(actual) EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s")
#define EXPECT_FALSE(actual) EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s")

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
	
	std::ifstream file;
	std::string temp;
	line cur_line;
	source source_file(argv[1]);
	int error_code = NO_ERROR;
	
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