#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Структура для передачі параметрів у потокову функцію
typedef struct {
    char *name;
    char *str;
    int num;
} ThreadParams;

// Потокова функція
void *print_strings(void *arguments) {
    ThreadParams *params = (ThreadParams *)arguments;
    for (int i = 0; i < params->num; ++i) {
        printf("%s. %s %d\n", params->name, params->str, i);
        // Додано затримку для ефектнішого чергування потоків
        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    ThreadParams params[4] = {
        {"Thread 1", "Fibbonacci", 3},
        {"Thread 2", "Eiler", 3},
        {"Thread 3", "Newton", 4},
        {"Thread 4", "Einstein", 3}
    };

    // Створення чотирьох потоків
    for (int i = 0; i < 4; ++i) {
        if (pthread_create(&threads[i], NULL, print_strings, (void *)&params[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Очікування завершення потоків
    for (int i = 0; i < 4; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    return 0;
}
