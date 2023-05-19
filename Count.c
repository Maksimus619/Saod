#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h> 

double wtime() { 
    struct timeval t; 
    gettimeofday(&t, NULL); 
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6; 
}

int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min; 
}

void counting_sort(int array[], int size, int max_value) {
    int counts[max_value + 1];
    int sorted[size];
    
    // Инициализируем массив counts нулями
    for (int i = 0; i <= max_value; i++) {
        counts[i] = 0;
    }
    
    // Считаем количество каждого элемента в массиве
    for (int i = 0; i < size; i++) {
        counts[array[i]]++;
    }
    
    // Вычисляем индексы начала каждого значения в массиве sorted
    for (int i = 1; i <= max_value; i++) {
        counts[i] += counts[i - 1];
    }
    
    // Сортируем массив
    for (int i = size - 1; i >= 0; i--) {
        sorted[counts[array[i]] - 1] = array[i];
        counts[array[i]]--;
    }
    
    // Копируем отсортированный массив обратно в исходный
    for (int i = 0; i < size; i++) {
        array[i] = sorted[i];
    }
}

int main() {
    int x; 
    scanf("%d", &x);
    
    double n = wtime(); 
    
    int mass[x], max = 0, min = 0, max1 = 100000; 
    for(int i = 0; i < x; i++) { //заполняем случайными числами
        mass[i] = getrand(min, max1); 
        if (max < mass[i]) { //проверят является ли текущее значение больше текущего максимального
            max = mass[i];
        } 
    }
    
    for(int i = 0; i < x; i++) { 
        printf("%d\n", mass[i]); 
    }
    
    // Используем counting sort для сортировки массива mass
    counting_sort(mass, x, max);
    
    for(int i = 0; i < x; i++) { 
        printf("%d\n", mass[i]); 
    } 
    
    double m = wtime(); 
    printf("%lf \n", m - n); 
    
    return 0; 
}



