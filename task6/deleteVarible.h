#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void deleteVariable(char* variable) {
    if (unsetenv(variable) == 0) {
        printf("Deleted %s from the environment.\n", variable);
    } else {
        printf("Failed to delete %s from the environment.\n", variable);
    }
}