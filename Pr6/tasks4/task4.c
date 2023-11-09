#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Структура для зберігання результатів обчислень
typedef struct {
    unsigned long long *values;
    int count;
} result_t;

// Функція для обчислення чисел Каталана
void *compute_catalan(void *args) {
    int n = *((int*)args);
    result_t *result = malloc(sizeof(result_t));
    result->values = malloc(n * sizeof(unsigned long long));
    result->count = n;

    result->values[0] = 1; // Перше число Каталана
    for (int i = 1; i < n; i++) {
        result->values[i] = result->values[i-1] * 2 * (2 * i - 1) / (i + 1);
    }

    return result;
}

// Допоміжна функція для перевірки чи число є простим
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    return 1;
}

// Функція для обчислення простих чисел
void *compute_primes(void *args) {
    int n = *((int*)args);
    result_t *result = malloc(sizeof(result_t));
    result->values = malloc(n * sizeof(unsigned long long));
    result->count = 0;

    for (int i = 2; result->count < n; ++i) {
        if (is_prime(i)) {
            result->values[result->count++] = i;
        }
    }

    return result;
}

int main() {
    pthread_t catalan_thread, prime_thread;
    int n_catalan = 15, n_primes = 12;
    
    // Створюємо потік для чисел Каталана
    if(pthread_create(&catalan_thread, NULL, compute_catalan, &n_catalan)) {
        fprintf(stderr, "Error creating thread for Catalan numbers\n");
        return 1;
    }

    // Створюємо потік для простих чисел
    if(pthread_create(&prime_thread, NULL, compute_primes, &n_primes)) {
        fprintf(stderr, "Error creating thread for prime numbers\n");
        return 1;
    }

    // Отримуємо результати з потоків
    result_t *catalan_result;
    result_t *primes_result;
    pthread_join(catalan_thread, (void**)&catalan_result);
    pthread_join(prime_thread, (void**)&primes_result);

   
    printf("Catalan numbers:\n");
    for (int i = 0; i < catalan_result->count; ++i) {
        printf("%llu ", catalan_result->values[i]);
    }
    printf("\n");


    printf("Prime numbers:\n");
    for (int i = 0; i < primes_result->count; ++i) {
        printf("%llu ", primes_result->values[i]);
    }
    printf("\n");

    // Очищаємо пам'ять
    free(catalan_result->values);
    free(catalan_result);
    free(primes_result->values);
    free(primes_result);

    return 0;
}
