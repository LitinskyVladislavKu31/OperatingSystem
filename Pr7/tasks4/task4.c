#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Глобальна змінна для зберігання тексту повідомлення
char *global_message;

void alarm_handler(int sig) {
    printf("%s\n", global_message); // Виведення повідомлення
    exit(0); // Завершення процесу
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <seconds> <message>\n", argv[0]);
        return 1;
    }

    int interval = atoi(argv[1]);
    global_message = argv[2];

    signal(SIGALRM, alarm_handler); // Встановлення обробника сигналу будильника

    pid_t pid = fork(); // Створення дочірнього процесу

    if (pid == 0) {
        // Дочірній процес
        alarm(interval); // Встановлення будильника
        pause();         // Очікування сигналу
    } else if (pid > 0) {
        // Батьківський процес
        wait(NULL); // Очікування завершення дочірнього процесу
    } else {
        // Помилка створення процесу
        perror("fork");
        return 2;
    }

    return 0;
}
