#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern char** environ;
void clearEnvironment() {
    while (*environ != NULL) {
        unsetenv(*environ);
        environ++;
    }
    printf("Cleared the entire environment.\n");
}