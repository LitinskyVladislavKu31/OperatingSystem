#include <stdio.h>
#include <stdlib.h>

// Початкова розмірність масиву
#define INITIAL_CAPACITY 10

// Структура для представлення ArrayList
typedef struct {
    int *data;         // Вказівник на масив
    int size;          // Кількість елементів у списку
    int capacity;      // Поточна ємність масиву
} ArrayList;

// Функція для створення нового ArrayList
ArrayList* createArrayList() {
    ArrayList *list = (ArrayList*)malloc(sizeof(ArrayList));
    list->data = (int*)malloc(sizeof(int) * INITIAL_CAPACITY);
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return list;
}

// Функція для додавання елемента в кінець списку
void add(ArrayList *list, int item) {
    if (list->size == list->capacity) {
        // Якщо список заповнений, збільшуємо ємність масиву
        int newCapacity = list->capacity * 2;
        list->data = (int*)realloc(list->data, sizeof(int) * newCapacity);
        list->capacity = newCapacity;
    }
    list->data[list->size] = item;
    list->size++;
}

// Функція для вставки елемента за індексом
void insert(ArrayList *list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Неприпустимий індекс для вставки\n");
        return;
    }
    if (list->size == list->capacity) {
        // Якщо список заповнений, збільшуємо ємність масиву
        int newCapacity = list->capacity * 2;
        list->data = (int*)realloc(list->data, sizeof(int) * newCapacity);
        list->capacity = newCapacity;
    }
    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = item;
    list->size++;
}

// Функція для отримання кількості елементів у списку
int size(ArrayList *list) {
    return list->size;
}

// Функція для видалення елемента за індексом
void removeItem(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Неприпустимий індекс для видалення\n");
        return;
    }
    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}

// Функція для зміни значення існуючого елемента за індексом
void set(ArrayList *list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Неприпустимий індекс для зміни\n");
        return;
    }
    list->data[index] = item;
}

// Функція для отримання значення елемента за індексом
int get(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Неприпустимий індекс для отримання\n");
        return -1; // Повертаємо -1 у випадку помилки
    }
    return list->data[index];
}

// Функція для виведення списку на екран
void printList(ArrayList *list) {
    printf("ArrayList: ");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// Функція для вивільнення ресурсів, відведених для ArrayList
void freeArrayList(ArrayList *list) {
    free(list->data);
    free(list);
}

int main() {
    ArrayList *list = createArrayList();

    // Додавання елементів
    add(list, 1);
    add(list, 2);
    add(list, 3);
    add(list, 7);
    add(list, 9);

    // Виведення списку
    printList(list);

    // Вставка елемента за індексом
    insert(list, 1, 4);
    insert(list, 5, 10);
    // Виведення списку
    printList(list);

    // Зміна значення елемента за індексом
    set(list, 2, 5);

    // Виведення списку
    printList(list);

    // Видалення елемента за індексом
    removeItem(list, 0);
    removeItem(list, 3);

    // Виведення списку
    printList(list);

    // Отримання кількості елементів
    printf("Кількість елементів: %d\n", size(list));

    // Отримання значення елемента за індексом
    int value = get(list, 1);
    printf("Значення за індексом 1: %d\n", value);

    // Звільнення пам'яті
    freeArrayList(list);

    return 0;
}
