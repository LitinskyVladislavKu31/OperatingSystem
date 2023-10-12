#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Функція для виведення значення змінної оточення
void printVariableValue(char* variable) {
    char* value = getenv(variable);
    if (value != NULL) {
        printf("%s=%s\n", variable, value);
    } else {
        printf("Variable '%s' is not in the environment.\n", variable);
    }
}
