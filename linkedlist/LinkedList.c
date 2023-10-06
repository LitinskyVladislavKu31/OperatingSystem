#include <stdio.h>
#include <stdlib.h>

// Структура для представлення елемента списку
typedef struct Node {
    int data;             // Дані, які зберігаються у вузлі
    struct Node* next;    // Вказівник на наступний вузол
} Node;

// Структура для представлення LinkedList
typedef struct {
    Node* head;    // Вказівник на голову списку
    int size;      // Кількість елементів у списку
} LinkedList;

// Функція для створення нового LinkedList
LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

// Функція для додавання елемента в кінець списку
void add(LinkedList* list, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
}

// Функція для вставки елемента за індексом
void insert(LinkedList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Неприпустимий індекс для вставки\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
}

// Функція для отримання кількості елементів у списку
int size(LinkedList* list) {
    return list->size;
}

// Функція для видалення елемента за індексом
void removeItem(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Неприпустимий індекс для видалення\n");
        return;
    }

    if (index == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }

    list->size--;
}

// Функція для заміни існуючого елемента за індексом
void set(LinkedList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Неприпустимий індекс для заміни\n");
        return;
    }

    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = item;
}

// Функція для отримання значення елемента за індексом
int get(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Неприпустимий індекс для отримання\n");
        return -1; // Повертаємо -1 у випадку помилки
    }

    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

// Функція для виведення списку на екран
void printList(LinkedList* list) {
    Node* current = list->head;
    printf("LinkedList: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Функція для вивільнення ресурсів, відведених для LinkedList
void freeLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList* list = createLinkedList();

    // Додавання елементів
    add(list, 1);
    add(list, 2);
    add(list, 3);
    add(list, 6);

    // Виведення списку
    printList(list);

    // Вставка елемента за індексом
    insert(list, 1, 4);

    // Виведення списку
    printList(list);

    // Заміна значення елемента за індексом
    set(list, 2, 5);
    set(list, 4, 7);

    // Виведення списку
    printList(list);

    // Видалення елемента за індексом
    removeItem(list, 0);

    // Виведення списку
    printList(list);

    // Отримання кількості елементів
    printf("Кількість елементів: %d\n", size(list));

    // Отримання значення елемента за індексом
    int value = get(list, 2);
    printf("Значення за індексом 2: %d\n", value);

    // Звільнення пам'яті
    freeLinkedList(list);

    return 0;
}
