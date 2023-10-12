#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern char** environ;
#pragma once
//Функція для встановлення значення змінної оточення
void setVariableValue(char* variable, char* value) {
    if (value == NULL) {
        value = "";
    }
    if (setenv(variable, value, 1) == 0) {
        printf("Set %s=%s\n", variable, value);
    } else {
        printf("Failed to set %s=%s\n", variable, value);
    }
}