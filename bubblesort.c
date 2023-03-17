#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n = 50000;
    int arr[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    bubbleSort(arr, n);
    gettimeofday(&t2, NULL);
    double elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
    printf("Elapsed time: %f ms\n", elapsedTime);
    return 0;
}
