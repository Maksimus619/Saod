#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) { // итерации по массиву
        for (j = 0; j < n-i-1; j++) { // итерации по неотсортированным элементам
            if (arr[j] > arr[j+1]) { // проверка на необходимость перестановки
                int temp = arr[j]; // временная переменная для перестановки
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n = 50000;
    int arr[n];
    srand(time(NULL)); // инициализация генератора случайных чисел
    for (int i = 0; i < n; i++) { // заполнение массива случайными числами
        arr[i] = rand();
    }
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);// сохранение времени перед сортировкой
    bubbleSort(arr, n); // вызов функции сортировки пузырьком
    gettimeofday(&t2, NULL); // сохранение времени после сортировки
    double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // секунды в миллисекунды
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // микросекунды в миллисекунды
    printf("Elapsed time: %f ms\n", elapsedTime);
    return 0;
}
