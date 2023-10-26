#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_HANDLERS 100

int registered_handlers_count = 0;
int handler_numbers[MAX_HANDLERS];

void handler_function() {
    sleep(1);
    if (registered_handlers_count > 0) {
        printf("Обробник %d завершив роботу\n", handler_numbers[--registered_handlers_count]);
    }
}

void register_handlers(int count) {
    for (int i = 0; i < count && i < MAX_HANDLERS; i++) {
        handler_numbers[i] = i + 1;
        registered_handlers_count++;
        atexit(handler_function);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <кількість обробників>\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);
    register_handlers(count);

    printf("Головна програма завершена\n");
    return 0;
}
