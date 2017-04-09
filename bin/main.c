#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <string.h>

typedef void (*func)();

void callback() {
	printf("callback!\n");
}

void invoker(func f) {
	f();
}

int main() {
char FBM[NUM_BLOCKS];
    char WM[NUM_BLOCKS];
    for (int i=1 ; i < (NUM_BLOCKS-2) ; i++) {
        printf("something %d\n", i);
        FBM[i] = 1;
        WM[i] = 1;
    }
}





















