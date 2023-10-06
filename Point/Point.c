#include <stdio.h>
#include <stdlib.h>

// Структура для представлення точки з масою та позицією
typedef struct {
    int position;
    int mass;
} Point;

// Функція для знаходження точки з найменшою масою
int findMinMass(Point* points, int n) {
    int minMass = points[0].mass;
    int minIndex = 0;

    for (int i = 1; i < n; i++) {
        if (points[i].mass < minMass) {
            minMass = points[i].mass;
            minIndex = i;
        }
    }

    return minIndex;
}

// Функція для моделювання процесу зникнення точок та знаходження залишеної точки
int findLastPoint(Point* points, int n) {
    while (n > 1) {
        int minIndex = findMinMass(points, n);
        int nearestLeft = (minIndex - 1 + n) % n; // Найближча точка зліва
        int nearestRight = (minIndex + 1) % n;   // Найближча точка зправа

        points[nearestLeft].mass += points[minIndex].mass; // Передача маси точці зліва
        for (int i = minIndex; i < n - 1; i++) {
            points[i] = points[i + 1]; // Видалення точки з масою
        }
        n--;
    }

    return points[0].position; // Повертаємо позицію залишеної точки
}

int main() {
    int n;

    printf("Введіть кількість точок: ");
    scanf("%d", &n);

    Point* points = (Point*)malloc(sizeof(Point) * n);

    printf("Введіть масу та позицію кожної точки:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].mass, &points[i].position);
    }

    int lastPointPosition = findLastPoint(points, n);
    printf("Залишена точка знаходиться на позиції: %d\n", lastPointPosition);

    free(points);

    return 0;
}
