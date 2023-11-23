#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h> 

// Глобальна змінна для визначення реакції на сигнал
int signal_type;

// Обробник сигналів для версії за допомогою signal
void signal_handler(int signo) {
    switch (signo) {
        case SIGINT:
            printf("Отримано сигнал SIGINT: Захоплення!\n");
            break;
        case SIGTERM:
            printf("Отримано сигнал SIGTERM: Захоплення!\n");
            break;
        case SIGUSR1:
            printf("Отримано сигнал SIGUSR1: Завершення роботи програми.\n");
            exit(0);
            break;
        case SIGPROF:
            // Відновлення поведінки за замовчуванням для SIGPROF
            signal(SIGPROF, SIG_DFL);
            break;
        default:
            break;
    }
}

// Обробник сигналів для версії за допомогою sigaction
void sigaction_handler(int signo) {
    switch (signo) {
        case SIGINT:
            printf("Отримано сигнал SIGINT: Захоплення!\n");
            break;
        case SIGTERM:
            printf("Отримано сигнал SIGTERM: Захоплення!\n");
            break;
        case SIGUSR1:
            printf("Отримано сигнал SIGUSR1: Завершення роботи програми.\n");
            exit(0);
            break;
        case SIGPROF:
            // Відновлення поведінки за замовчуванням для SIGPROF
            struct sigaction sa_default;
            sa_default.sa_handler = SIG_DFL;
            sa_default.sa_flags = 0;
            sigaction(SIGPROF, &sa_default, NULL);
            break;
        default:
            break;
    }
}

int main() {
    // Виберіть тип сигналу для використання
    printf("Виберіть тип сигналу (1 - signal, 2 - sigaction): ");
    scanf("%d", &signal_type);

    // Встановлення обробників сигналів
    if (signal_type == 1) {
        signal(SIGINT, signal_handler);
        signal(SIGTERM, signal_handler);
        signal(SIGUSR1, signal_handler);
        signal(SIGPROF, signal_handler);
    } else if (signal_type == 2) {
        struct sigaction sa;
        sa.sa_handler = sigaction_handler;
        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask);

        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGTERM, &sa, NULL);
        sigaction(SIGUSR1, &sa, NULL);
        sigaction(SIGPROF, &sa, NULL);
    } else {
        printf("Неправильний вибір. Введіть 1 або 2.\n");
        return 1;
    }

    // Встановлення ігнорування сигналу SIGHUP
    signal(SIGHUP, SIG_IGN);

    // Безкінечний цикл з паузою
    while (1) {
        pause();
    }

    return 0;
}
