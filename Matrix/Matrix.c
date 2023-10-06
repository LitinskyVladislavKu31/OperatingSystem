#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функція для виділення пам'яті та ініціалізації матриці рандомними значеннями
void createAndFillMatrix(int ***matrix, int *rows, int *cols) {
    printf("Введіть кількість рядків: ");
    scanf("%d", rows);

    printf("Введіть кількість стовпців: ");
    scanf("%d", cols);

    // Виділення пам'яті для матриці
    *matrix = (int ** )malloc((*rows) * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = (int *)malloc((*cols) * sizeof(int));
    }

    // Ініціалізація генератора випадкових чисел
    srand(time(NULL));

    // Заповнення матриці рандомними значеннями
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            (*matrix)[i][j] = rand() % 100; // Генеруємо випадкове число від 0 до 99
        }
    }
    printf("Матриця створена \n");
}

// Функція для виведення матриці
void printMatrix(int **matrix, int rows, int cols) {
    printf("Матриця:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функція для зміни елемента матриці
void changeMatrixElement(int **matrix, int rows, int cols, int row, int col, int newValue) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        matrix[row][col] = newValue;
        printf("Елемент матриці змінено.\n");
    } else {
        printf("Недійсні координати елемента.\n");
    }
}
// Функція для звільнення пам'яті від матриці
void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Функція для додавання двох матриць
void addMatrices(int **matrix1, int **matrix2, int ***result, int rows, int cols) {
    *result = (int ** )malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        (*result)[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*result)[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// Функція для віднімання однієї матриці від іншої
void subtractMatrices(int **matrix1, int **matrix2, int ***result, int rows, int cols) {
    *result = (int ** )malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        (*result)[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*result)[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

// Функція для множення матриці на число
void multiplyMatrixByScalar(int **matrix, int ***result, int rows, int cols, int scalar) {
    *result = (int ** )malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        (*result)[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*result)[i][j] = matrix[i][j] * scalar;
        }
    }
}

// Функція для множення двох матриць
void multiplyMatrices(int **matrix1, int **matrix2, int ***result, int rows1, int cols1, int cols2) {
    *result = (int **)malloc(rows1 * sizeof(int *));
    for (int i = 0; i < rows1; i++) {
        (*result)[i] = (int *)malloc(cols2 * sizeof(int));
    }

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            (*result)[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                (*result)[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}


void saveMatrixToFile(int **matrix, int rows, int cols, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Не вдалося відкрити файл для запису.\n");
        return;
    }

    fprintf(file, "%d %d\n", rows, cols); // Записуємо розмір матриці

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]); // Записуємо елементи матриці
        }
        fprintf(file, "\n"); // Перехід на новий рядок
    }

    fclose(file);
    printf("Матрицю збережено в файлі %s\n", filename);
}

// Функція для читання матриці з файлу
void readMatrixFromFile(int ***matrix, int *rows, int *cols, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Не вдалося відкрити файл для читання.\n");
        return;
    }

    fscanf(file, "%d %d", rows, cols); // Зчитуємо розмір матриці

    // Виділення пам'яті для матриці
    *matrix = (int **)malloc((*rows) * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = (int *)malloc((*cols) * sizeof(int));
    }

    // Зчитуємо елементи матриці з файлу
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d", &((*matrix)[i][j]));
        }
    }

    fclose(file);
    printf("Матрицю зчитано з файлу %s\n", filename);
}


int main() {
    int rows1, cols1, rows2, cols2;
    int **matrix1 = NULL, **matrix2 = NULL, **result = NULL;

    int ch;
    while (1) {
        printf("1.Створити матрицю\n2.Вивести матрицю\n3.Змінити елемент матриці\n4.Видалення матриці \n5. Додати матриці\n6. Відняти матриці\n7. Множення матриці на число\n8. Множення матриць\n9.Зберегти у файл\n10.Зчитати матрицю з файлу\n11.Вихід\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
            if (matrix1 != NULL) {
                    printf("Матриця вже створена. Видаліть її перед створенням нової.\n");
                } else {
                    createAndFillMatrix(&matrix1, &rows1, &cols1);
                }
                break;

            case 2:
                if (matrix1 == NULL) {
                    printf("Матриця не створена.\n");
                } else {
                    printMatrix(matrix1, rows1, cols1);
                }
                printf("Count rows %d\n",rows1);
                printf("Count cols %d\n",cols1);
                break;


            case 3:
                if (matrix1) {
                    int row, col, newValue;
                    printf("Введіть рядок та стовпець елемента, який потрібно змінити: ");
                    scanf("%d %d", &row, &col);
                    printf("Введіть нове значення: ");
                    scanf("%d", &newValue);

                    changeMatrixElement(matrix1, rows1, cols1, row, col, newValue);
                } else {
                    printf("Матриця не була створена.\n");
                }
                break;

                case 4:
                if (matrix1 == NULL) {
                    printf("Матриця не створена.\n");
                } else {
                    freeMatrix(matrix1, rows1);
                    matrix1 = NULL;
                    printf("Матрицю видалено.\n");
                }
                break;
            
              case 5:
               if (matrix1 == NULL) {
                    printf("Спершу створіть матрицю.\n");
                } else {
                    if (matrix2 != NULL) {
                        printf("Друга матриця вже створена. Видаліть її перед створенням нової.\n");
                    } else {
                        createAndFillMatrix(&matrix2, &rows2, &cols2);
                        if (rows1 != rows2 ||cols1 != cols2) {
                            printf("Матриці мають різний розмір, операція додавання неможлива.\n");
                            freeMatrix(matrix2, rows2);
                            matrix2 = NULL;
                        } else {
                            printMatrix(matrix1, rows1, cols1);
                            printMatrix(matrix2, rows2, cols2);
                            addMatrices(matrix1, matrix2, &result, rows1, cols1);
                            printf("Результат додавання матриць:\n");
                            printMatrix(result, rows1, cols1);
                            freeMatrix(result, rows1);
                            result = NULL;
                        }
                    }
                }
                break;

            case 6:
                if (matrix1 == NULL ||  matrix2 == NULL) {
                    printf("Спершу створіть дві матриці однакового розміру.\n");
                } else {
                    subtractMatrices(matrix1, matrix2, &result, rows1, cols1);
                    printf("Результат віднімання матриць:\n");
                    printMatrix(result, rows1, cols1);
                    freeMatrix(result, rows1);
                    result = NULL;
                }
                break;

            case 7:
                if (matrix1 == NULL) {
                    printf("Спершу створіть матрицю.\n");
                } else {
                    int scalar;
                    printf("Введіть скаляр: ");
                    scanf("%d", &scalar);
                    multiplyMatrixByScalar(matrix1, &result, rows1, cols1, scalar);
                    printf("Результат множення матриці на скаляр:\n");
                    printMatrix(result, rows1, cols1);
                    freeMatrix(result, rows1);
                    result = NULL;
                }
                break;

            case 8:
                if (matrix1 == NULL || matrix2 == NULL) {
                    printf("Спершу створіть дві матриці і переконайтеся, що їх розміри допустимі для множення.\n");
                } else {
                    multiplyMatrices(matrix1, matrix2, &result, rows1, cols1, cols2);
                    printf("Результат множення матриць:\n");
                    printMatrix(result, rows1, cols2);
                    freeMatrix(result, rows1);
                    result = NULL;
                }
                break;
                
                
                 case 9:
                if (matrix1 == NULL) {
                    printf("Матриця не створена.\n");
                } else {
                    char filename[256];
                    printf("Введіть ім'я файлу для збереження матриці: ");
                    scanf("%s", filename);
                    saveMatrixToFile(matrix1, rows1, cols1, filename);
                }
                break;

                case 10:
                if (matrix1 != NULL) {
                    printf("Матрицю вже створено. Завантажте матрицю з файлу після її видалення.\n");
                } else {
                    char filename[256];
                    printf("Введіть ім'я файлу для зчитування матриці: ");
                    scanf("%s", filename);
                    readMatrixFromFile(&matrix1, &rows1, &cols1, filename);
                }
                break;
                
                

            case 11:
                printf("До зустрічі!\n");
                if (matrix1 != NULL) {
                    freeMatrix(matrix1, rows1);
                }
                if (matrix2 != NULL) {
                    freeMatrix(matrix2, rows2);
                }
                if (result != NULL) {
                    freeMatrix(result, rows1);
                }
                exit(0);
                break;

            default:
                printf("Вибрана невірна опція. Спробуйте ще раз.\n");
        }
    }

    return 0;
}