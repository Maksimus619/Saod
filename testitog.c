#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Node {
    int data;
    int level;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

// ... (оставшаяся часть кода без изменений)

int main() {
    Node* root = NULL;
    int values_count = 100000;

    // Инициализация генератора случайных чисел
    srand((unsigned int)time(NULL));

    // Засекаем время перед выполнением операций
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Генерация и добавление случайных значений
    for (int i = 0; i < values_count; i++) {
        int random_value = rand() % (values_count * 10);
        root = insert(root, random_value);
    }

    // Добавление случайного значения
    int random_insert_value = rand() % (values_count * 10);
    if (!isNodePresent(root, random_insert_value)) {
        root = insert(root, random_insert_value);
        printf("Random element added: %d\n", random_insert_value);
    } else {
        printf("Element already exists.\n");
    }

    // Удаление случайного значения
    int random_delete_value = rand() % (values_count * 10);
    if (isNodePresent(root, random_delete_value)) {
        root = deleteNode(root, random_delete_value);
        printf("Random element deleted: %d\n", random_delete_value);
    } else {
        printf("Element not found.\n");
    }

    // Засекаем время после выполнения операций
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000.0 + (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

    printf("Прошедшее время: %.2f миллисекунд\n", elapsed_time);

    return 0;
}
