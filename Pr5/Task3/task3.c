#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

#define DEFAULT_BUFFER_SIZE 127



int main(int argc, char* argv[]) {
    char* username = "user";  // Це тимчасове ім'я користувача. За потреби ви можете змінити його.
    int bufferSize = 127;

    // Обробка аргументів командного рядка
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Help information...\n");
            return 0;
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) {
            if (i + 1 < argc) {
                bufferSize = atoi(argv[i + 1]);
                i++;
            } else {
                printf("No buffer size provided!\n");
                return 1;
            }
        }
    }

    char* command = malloc(bufferSize * sizeof(char));

    printf("Вітаємо, %s!\n", username);

   while (1) {
    printf("[%s]$", username);
    fgets(command, bufferSize, stdin);
    command[strlen(command) - 1] = '\0';  // Видаляємо символ нового рядка

    if (strcmp(command, "help") == 0 || strcmp(command, "-h") == 0 || strcmp(command, "--help") == 0) {
        printf("MyShell - це спрощена командна оболонка.\n");
        printf("Введіть команду для виконання.\n");
        printf("Доступні вбудовані команди:\n");
        printf("help, -h, --help - ця довідка\n");
        printf("buffer, -b, --buffer - встановити розмір буфера (після цієї команди введіть розмір)\n");
        printf("stop - завершити роботу оболонки\n");
    } else if (strcmp(command, "buffer") == 0 || strcmp(command, "-b") == 0 || strcmp(command, "--buffer") == 0) {
        printf("Введіть новий розмір буфера: ");
        int newBufferSize;
        scanf("%d", &newBufferSize);
        getchar();  // Зчитуємо символ нового рядка після числа
        if (newBufferSize > 0) {
            bufferSize = newBufferSize;
            free(command);  // Звільняємо старий буфер
            command = malloc(bufferSize * sizeof(char));  // Виділяємо пам'ять під новий буфер
        } else {
            printf("Недійсний розмір буфера.\n");
        }
    } else if (strcmp(command, "stop") == 0) {
        printf("Wait 3 seconds...\n");
        sleep(3);
        system("clear");
        exit(0);
    } else {
        system(command);  // Виконуємо команду
    }
}


    free(command);  // Цей рядок ніколи не буде досягнутий, але це хороша практика звільнення виділеної пам'яті
    return 0;
}
