#include "lex_config.h"
#include "test.h"
#include "token.h"
#include "symseg.h"
#include "lex.h"


extern std::string cur_line;
extern line cur_line_info;

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
	
	std::vector<std::string> test_error = {
		"			int 3a;									", /* invalid identifier */
		"			int b = 123.456.789;					", /* too many decimal points in number */
		"			int c = 09;								", /* too many decimal points in number */
	}
	
	for (std::string s : test_data) {
		cur_line = s;
		cur_line_info++;
		lex();
	}
}