//LambLexer
//by James 2017/04/20

#include "config.h"
#include "token.h"
#include "symbol_table.h"
#include "lex.h"
#include "parser.h"
#include "error.h"

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
	
#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_STRING(expect, actual) \
    EXPECT_EQ_BASE(actual.compare(expect) == 0, expect, actual.c_str(), "%s")
#define EXPECT_EQ_SIZE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%zu")


#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")
#define EXPECT_TRUE(actual) EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s")
#define EXPECT_FALSE(actual) EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s")

#define GET_TOKEN_TYPE(idx) source_file.get_token_type(idx)
#define GET_TOKEN_NAME(idx) source_file.get_token_name(idx)

static int test_count = 0;
static int test_pass = 0;
static int main_ret = 0;

void lexer::test_lexer() {
	
	/* Test operator */
	const std::vector<std::string> test_operator = {	
		" 			=!><+-*/%&|^>><<~&&||?:,				",
		"			()==!=>=<=+=-=*=/=%=&=|=				",
		"			^=>>=<<=[]{};++--->.::					",
	};
	
	for (std::string s : test_operator) {
		cur_line = s;
		cur_line_info++;
		cur_line_info.set_content(cur_line);
		source_file.push_line(cur_line_info);
		lex();
	}
	int i = 0;
	for ( ; i < 46; i++) {
		EXPECT_EQ_INT(i, GET_TOKEN_TYPE(i));
	}
	
	
	/* Test number */
	const std::vector<std::string> test_number = {
		"			int a = 123;							",
		"			int b = 123.456;						",
		"			int c = 0xff00;							",
		"			int d = 0123;							",
	};
	
	for (std::string s : test_number) {
		cur_line = s;
		cur_line_info++;
		cur_line_info.set_content(cur_line);
		source_file.push_line(cur_line_info);
		lex();
	}
	i += 3;  // index of "123"
	EXPECT_EQ_INT(C_NUMBER, GET_TOKEN_TYPE(i));
	EXPECT_EQ_STRING("123", GET_TOKEN_NAME(i));
	i += 5; // index of "123.456"
	EXPECT_EQ_INT(C_NUMBER, GET_TOKEN_TYPE(i));
	EXPECT_EQ_STRING("123.456", GET_TOKEN_NAME(i));
	i += 5; // index of "0xff00"
	EXPECT_EQ_INT(C_NUMBER, GET_TOKEN_TYPE(i));
	EXPECT_EQ_STRING("0xff00", GET_TOKEN_NAME(i));
	i += 5; // index of "0123"
	EXPECT_EQ_INT(C_NUMBER, GET_TOKEN_TYPE(i));
	EXPECT_EQ_STRING("0123", GET_TOKEN_NAME(i));
	
	/* Test identifier */
	const std::vector<std::string> test_identifier = {
		"			int identifier;							",
		"			int _identifier; 						",
		"			int _identifier_1_plus;					",
	};
	
	for (std::string s : test_identifier) {
		cur_line = s;
		cur_line_info++;
		cur_line_info.set_content(cur_line);
		source_file.push_line(cur_line_info);
		lex();
	}
	i += 3; // index of "identifier"
	EXPECT_EQ_INT(C_NAME, GET_TOKEN_TYPE(i));
	EXPECT_EQ_STRING("identifier", GET_TOKEN_NAME(i));
	i += 3; // index of "_identifier"
	EXPECT_EQ_INT(C_NAME, GET_TOKEN_TYPE(i));
	EXPECT_EQ_STRING("_identifier", GET_TOKEN_NAME(i));
	i += 3; // index of "_identifier_1_plus"
	EXPECT_EQ_INT(C_NAME, GET_TOKEN_TYPE(i));
	EXPECT_EQ_STRING("_identifier_1_plus", GET_TOKEN_NAME(i));
	
	/* Test comment */
	const std::vector<std::string> test_comment = {
		"			//This is a single line comment			",
		"			/* This is a							",
		"			 * multi-line							",
		"			 * ×¢ÊÍ									",
		"			 */										",
	};
	
	for (std::string s : test_comment) {
		cur_line = s;
		cur_line_info++;
		cur_line_info.set_content(cur_line);
		source_file.push_line(cur_line_info);
		lex();
	}
	i += 2; // The size of token stream
	EXPECT_EQ_SIZE(static_cast<size_t>(i), source_file.get_token_size());
	
	/* Test literal */
	const std::vector<std::string> test_literal = {
		"			string s = \"hello, \\\"world\";		",
		"			char c = 'b';							",
	};
	
	for (std::string s : test_literal) {
		cur_line = s;
		cur_line_info++;
		cur_line_info.set_content(cur_line);
		source_file.push_line(cur_line_info);
		lex();
	}
	i += 3; // index of "hello "world "
	EXPECT_EQ_INT(C_STRING, GET_TOKEN_TYPE(i));
	EXPECT_EQ_STRING("hello, \\\"world", GET_TOKEN_NAME(i));
	i += 5; // index of "b"
	EXPECT_EQ_INT(C_CHAR, GET_TOKEN_TYPE(i));
	EXPECT_EQ_STRING("b", GET_TOKEN_NAME(i));
	
	/* Test keywords */
	
	const std::vector<std::string> test_keywords = {
		"			static unsigned long const				",
		"			extern short volatile signed			",
		"			auto int char float						",
		"			double void enum struct					",
		"			union while do for						",
		"			goto switch case default				",
		"			break if else continue return			",
		"			sizeof									",
	};
	
	for (std::string s : test_keywords) {
		cur_line = s;
		cur_line_info++;
		cur_line_info.set_content(cur_line);
		source_file.push_line(cur_line_info);
		lex();
	}
	i += 2; // index of "static"
	for (int rid = 100; rid < 130; rid++, i++) {
		EXPECT_EQ_INT(rid, GET_TOKEN_TYPE(i));
	}
	
	/* Test Unknow type */
	const std::vector<std::string> test_stray_punctuation = {
		" 			@ $										",
	};
	
	for (std::string s : test_stray_punctuation) {
		cur_line = s;
		cur_line_info++;
		cur_line_info.set_content(cur_line);
		source_file.push_line(cur_line_info);
		lex();
	}
	EXPECT_EQ_INT(C_OTHER, GET_TOKEN_TYPE(i));
	i += 1;
	EXPECT_EQ_INT(C_OTHER, GET_TOKEN_TYPE(i));
	
#ifdef DUMP_TOKEN_STREAM
    dump_token_stream();
#endif /* end of DUMP_TOKEN_STREAM */

	source_file.reset(); // delete all the tokens
	cur_line_info.reset(); // reset the line information
	printf("Lexer Test: %d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
}

void lexer::test_parser_aux() {
	const std::vector<std::string> test_expr = {
		"        a + 2 * c - d;					",
		"        if (a == b) {					",
		"            a = a + b;					",
		"        } else {						",
		"            b = b + a * (d - c);		",
		"        }								",
		// "  a + b * c / (d * 5) - k;					",
		// "  first + (second * third;								",
		// "  b + ;									",
		// "  for(;;);								",
		// "  for(i = 0;;);						",
		// "  for(i = 0; i < 5;);					",
		// "  for(i = 0; i < 5; i = i + 1);		",
		// "  for(i = 0; i < 5;					",
	};
	std::cout << "    source code: " << std::endl;
	for (std::string s : test_expr) {
		std::cout << s << std::endl;
		cur_line = s;
		cur_line_info++;
		cur_line_info.set_content(cur_line);
		source_file.push_line(cur_line_info);
		lex();
	}
	std::cout << std::endl;
	std::cout << "    pseudo-code: " << std::endl;
}













