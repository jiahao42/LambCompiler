// LambLexer
// by James 2017/04/06

#include "util.h"
#include "config.h"
#include "symbol_table.h"
#include "token.h"


/*
 * ELFHash, used for access varible in Symbol Table faster
 */
unsigned int ELFHash(std::string str) {
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;
    unsigned int len = str.length();

    for (i = 0; i < len; i++) {
        hash = (hash << 4) + (str[i]);
        if ((x = hash & 0xF0000000) != 0) {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }
    return hash;
}

/*
 * Help menu
 */
void help_menu() {
    std::cout << "This compiler has two modes: test mode and normal mode\n"
                 "In test mode, it just uses the test data inside\n"
                 "In normal mode, you can compile file outside\n"
                 "You can modify the macro in config.h to change the mode\n\n"
                 "Usage:\n"
                 "\t./compiler [filename]\n"
                 "\t./compiler -v see the version of this compiler\n"
                 "\t./compiler -h see the help menu of this compiler\n"
              << std::endl;
}

/*
 * Show version
 */
void show_version() {
    std::cout << "LambCompiler, Version: " << version << std::endl << std::endl;
    ;
}
