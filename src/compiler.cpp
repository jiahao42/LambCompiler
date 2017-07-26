// LambCompiler
// by James 2017/05/02
#include "compiler.h"
#include "config.h"

extern std::ifstream file;       /* Current file */
extern symbol_root symbol_table; /* Symbol table, see symbol_table.h */
extern source source_file; /* Stand for source file, including filename and
                              lines' info, See symbol_table.h */
extern std::vector<std::string> code;

int compiler::compile(int argc, char **argv) {
    init_symbol_table("test_dummy", "test_dummy");
#ifdef TEST_ON
    l.test_lexer();
    test_parser();
#else
    if (argc == 1) {
        help_menu();
        return 0;
    }
    if (argv[1][0] == '-') {
        switch (argv[1][1]) {
        case 'h':
            help_menu();
            break;
        case 'v':
            show_version();
            break;
        default:
            std::cout << "Unknown parameter, please check again" << std::endl
                      << std::endl;
        }
    } else {
        std::cout << "    source code: " << std::endl;
        init_symbol_table(argv[0], argv[1]);
        l.read_file();
        std::cout << std::endl;
        std::cout << "    pseudo-code: " << std::endl;
        p.parse_main();
    }
#endif /* end of TEST_ON */

#ifdef DUMP_TOKEN_STREAM
    l.dump_token_stream();
#endif /* end of DUMP_TOKEN_STREAM */
    // v.execute_code();
    std::cout << std::endl;
    return 0;
}

void compiler::test_parser() {
    std::cout << "    source code: " << std::endl;
    l.test_parser_aux();
    std::cout << std::endl;
    std::cout << "    pseudo-code: " << std::endl;
    p.parse_main();
}