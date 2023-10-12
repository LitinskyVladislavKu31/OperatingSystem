#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функція для виведення значення змінної оточення
void printEnvironmentVariable(const char *name) {
    char *value = getenv(name);
    if (value != NULL) {
        printf("1.Значення змінної оточення %s: %s\n", name, value);
    } else {
        printf("Змінна оточення %s не знайдена.\n", name);
    }
}

// Функція для виведення всіх змінних оточення
void printAllEnvironmentVariables(char *envp[]) {
    printf("2.Усі змінні оточення:\n");
    for (char **env = envp; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

int main(int argc, char *argv[], char *envp[]) {
   if (argc == 2) {
        printEnvironmentVariable(argv[1]);
    } else if (argc == 1) {
        printf("Введіть ім'я змінної оточення: ");
        char input[256];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Видаляємо символ нового рядка, який додає fgets
        printEnvironmentVariable(input);
    } else {
        printf("Неправильна кількість аргументів командного рядка.\n");
    }

    // Виведення всіх змінних оточення
     if (argc == 1) {
        printAllEnvironmentVariables(envp);
    }

    return 0;
}

