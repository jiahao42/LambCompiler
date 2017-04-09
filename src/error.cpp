#include "lex_config.h"
#include "error.h"

/*
 * Output the error to the console
 */
#define ERROR(ERR_ID, idx) std::cout << source_file.filename << ":" << cur_line_info.linenum << ":" << idx << " Error:" << ERROR_STRING[ERR_ID] << std::endl

#define WARNING(WARNING_ID, idx) std::cout << source_file.filename << ":" << cur_line_info.linenum << ":" << idx << " Warning:" << WARNING_STRING[WARNING_ID] << std::endl

extern source source_file;
std::queue<_error> error_queue;
std::queue<_warning> warning_queue;


/*
 * Push the error into the queue
 */
#define PUSH_ERROR(linenum, col, ERR_ID) \
	do {\
		_error e(ERR_ID, linenum, col);\
		error_queue.push(e);\
	}while(0);
	
#define PUSH_WARNING(linenum, col, WARNING_ID) \
	do {\
		_warning w(WARNING_ID, linenum, col);\
		warning_queue.push(w);\
	}

/*
 * Output the error to the console
 */
#define POP_ERROR() \
	do {\
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	

