#include "lex_config.h"
#include "test.h"
#include "token.h"
#include "symseg.h"
#include "lex.h"

#ifdef TEST_ON
/*
 * Simple Test Framework
 */
#define EXPECT_EQ_BASE(equality,expect,actual,format)	\
	do {	\
		test_count++;	\
		if (equality){	\
			test_pass++;\
		}else{	\
			main_ret = 1;	\
			fprintf(stderr,"%s:%d: expect: " format " actual: " format "\n",__FILE__,__LINE__,expect,actual);\
		}	\
	}while (0)

#else
#define EXPECT_EQ_BASE(equality, expect, actual, format) do{} while(0)
#endif /* end of TEST_ON */
	
#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")
#define EXPECT_EQ_STRING(expect, actual, alength) \
    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength + 1) == 0, expect, actual, "%s")
#define EXPECT_TRUE(actual) EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s")
#define EXPECT_FALSE(actual) EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s")


extern std::string cur_line;
extern line cur_line_info;
extern source source_file;

int test_count = 0;
int test_pass = 0;
int main_ret = 0;

void test_lexer() {
	std::vector<std::string> test_operator = {	
		" 			=!><+-*/%&|^>><<~&&||?:,				",
		"			()==!=>=<=+=-=*=/=%=&=|=				",
		"			^=>>=<<=[]{};++--->.::					",
	};
	
	std::vector<std::string> test_number = {
		"			int a = 123;							",
		"			int b = 123.456;						",
		"			int c = 0xff00;							",
		"			int d = 0123;							",
	};
	
	std::vector<std::string> test_identifier = {
		"			int a;									",
		"			int _b;			 						",
		"			int _c_d_1;								",
	};
	
	std::vector<std::string> test_comment = {
		"			//This is a single line comment			",
		"			/* This is a							",
		"			 * multi-line							",
		"			 * ×¢ÊÍ									",
		"			 */										",
	};
	
	std::vector<std::string> test_literal = {
		"			string s = \"hello, \\\"world\";		",
		"			char c = 'b';							",
	};
	
	std::vector<std::string> test_warning_and_error = {
		"			int 3a;									", /* invalid identifier */
		"			ÖÐÎÄ									", /* unknown type name */
		"			int b = 123.456.789;					", /* too many decimal points in number */
		"			int c = 09;								", /* too many decimal points in number */
		"			string s = \"hello;						", /* missing terminating \" character */
		"			char cc = 'h;							", /* missing terminating \' character */
		"			cc = 'hello world';						", /* character constant too long for its type */
	};
	
	for (std::string s : test_operator) {
		cur_line = s;
		cur_line_info++;
		lex();
	}
	EXPECT_EQ_INT(C_EQ, source_file.get_token(0));
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
}















