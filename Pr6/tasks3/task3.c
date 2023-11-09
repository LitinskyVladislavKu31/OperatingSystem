#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Структура для передачі параметрів у потоки
typedef struct {
    char *string; 
    int count;    
    int range;    
    int stop_number; 
} thread_params_t;

// Функція потоку для друкування рядка
void *print_strings(void *parameters) {
    thread_params_t *params = (thread_params_t *)parameters;
    
    for (int i = 0; i < params->count; i++) {
        printf("Parent thread: %s %d\n", params->string, i);
        sleep(1); // Затримка між ітераціями
    }
    return NULL;
}

// Функція потоку для генерації випадкових чисел
void *generate_random_numbers(void *parameters) {
    thread_params_t *params = (thread_params_t *)parameters;
    int number;

    srand(time(NULL)); // Ініціалізація генератора випадкових чисел

    for (int i = 0; i < params->count; i++) {
        number = rand() % params->range;
        printf("Random Thread: %d\n", number);
        if (number == params->stop_number) {
            printf("Random Thread: Stopped as the stop number %d was generated.\n", params->stop_number);
            return NULL;
        }
        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t print_thread, random_thread;
    thread_params_t print_params = {.string = "Rainbow", .count = 6};
    thread_params_t random_params = {.count = 10, .range = 100, .stop_number = 42};

    // Створення потоку для друкування рядка
    if(pthread_create(&print_thread, NULL, &print_strings, &print_params)) {
        fprintf(stderr, "Error creating print thread\n");
        return 1;
    }

    // Створення потоку для генерації випадкових чисел
    if(pthread_create(&random_thread, NULL, &generate_random_numbers, &random_params)) {
        fprintf(stderr, "Error creating random number thread\n");
        return 1;
    }

    // Очікування завершення потоків
    pthread_join(print_thread, NULL);
    pthread_join(random_thread, NULL);

  
    printf("Main Thread: The child threads have completed.\n");

    return 0;
}
