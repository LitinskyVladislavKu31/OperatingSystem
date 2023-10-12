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
    int ch;
     char variableName[100];
     char variableValue[100];
        while (1) {
            printf("1.Змінити змінну оточення\n2.Видалити змінну оточення\n3.Exit\n");
            scanf("%d",&ch);
            switch(ch){

           case 1:
               printf("Введіть ім'я змінної: ");
                scanf("%s", variableName);

                printf("Введіть значення змінної: ");
                scanf("%s", variableValue);

                if (setenv(variableName, variableValue, 1) == 0) {
                    printf("Змінну оточення %s було успішно оновлено.\n", variableName);
                } else {
                    printf("Помилка при оновленні змінної оточення %s.\n", variableName);
                }
                if (argc == 1) {
                    printAllEnvironmentVariables(envp);
                }
                break;

             case 2:
                printf("Введіть ім'я змінної для видалення: ");
                scanf("%s", variableName);
                
                    if (unsetenv(variableName) == 0) {
                        printf("Змінну оточення %s було успішно видалено.\n", variableName);
                    } else {
                        printf("Помилка при видаленні змінної оточення %s.\n", variableName);
                    }
                
                if (argc == 1) {
                    printAllEnvironmentVariables(envp);
                }
                break;

            case 3:
            printf("До зустрічі\n");
            exit(0);
            break;
        default:
        printf("ERROR");
        break;
        }
        }
    

    return 0;
}
