#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printAllEnvironmentVariables(char *envp[]) {
    printf("Усі змінні оточення:\n");
    for (char **env = envp; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    
        while (1) {
            char variableName[100];
            char variableValue[100];

            printf("Введіть ім'я змінної (або 'exit' для виходу): ");
            fgets(variableName, sizeof(variableName), stdin);

            // Перевірка на виход з циклу
            if (strcmp(variableName, "exit\n") == 0) {
                break;
            }

            // Видалення символу нового рядка з імені змінної
            variableName[strlen(variableName) - 1] = '\0';

            printf("Введіть значення змінної: ");
            fgets(variableValue, sizeof(variableValue), stdin);

            // Видалення символу нового рядка зі значення змінної
            variableValue[strlen(variableValue) - 1] = '\0';

            if (setenv(variableName, variableValue, 1) == 0) {
                printf("Змінну оточення %s було успішно оновлено.\n", variableName);
            } else {
                printf("Помилка при оновленні змінної оточення %s.\n", variableName);
            }
            if (argc == 1) {
        printAllEnvironmentVariables(envp);
            
        
    } else {
        printf("Неправильна кількість аргументів. Використовуйте: програма ЗМІННА ЗНАЧЕННЯ\n");
    }
        }

    return 0;
}
