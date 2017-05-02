#include "lex_config.h"
#include "compiler.h"

std::ifstream file; 				/* Current file */
symbol_root symbol_table; 			/* Symbol table, see symseg.h */
source source_file; 				/* Stand for source file, including filename and lines' info, See symseg.h */

int compiler::compile(int argc, char** argv) {
	#ifdef TEST_ON
		init_symbol_table("test_dummy", "test_dummy");
		l.test_lexer();
	#else
		if (argc == 1) {
			std::cout << "Invalid parameter!" << std::endl;
			return 0;
		}
		if (argv[1][0] == '-') {
			switch(argv[1][1]) {
				case 'h':
					help_menu();
					break;
				case 'v':
					show_version();
					break;
				default:
					std::cout << "Unknown parameter, please check again" << std::endl << std::endl;
			}
		}else {
			init_symbol_table(argv[0], argv[1]);
			l.read_file();
		}
	#endif /* end of TEST_ON */

	#ifdef DUMP_TOKEN_STREAM
		l.dump_token_stream();
	#endif /* end of DUMP_TOKEN_STREAM */
	return 0;
}