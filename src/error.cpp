#include "lex_config.h"
#include "error.h"

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
		while(!error_queue.empty()) {\
			cout << error_queue.top();\
		}\
	}while(0)
	
#define POP_WARNING() \
	do {\
		while(!warning_queue.empty()) {\
			cout << warning_queue.top();\
		}\
	}while(0)
	
	
	
	
	
	
	
	
	
	
	

