#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "setVariableValue.h"
// Функція для призначення нового значення змінній оточення
void assignVariableValue(char* variable, char* value) {
    if (variable == NULL) {
        printf("Variable name not specified.\n");
        return;
    }
    setVariableValue(variable, value);
}