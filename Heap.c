#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double wtime()
{
struct timeval t;
gettimeofday(&t, NULL);
return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

// Функция "просеивания" через кучу - формирование кучи
void siftDown(int *arr, int x, int bottom)
{
  int max; // индекс максимального потомка
  int done = 0; // флаг того, что куча сформирована
  // Пока не дошли до последнего ряда
  while ((x * 2 <= bottom) && (!done)) 
  {
    if (x * 2 == bottom)    // если мы в последнем ряду,
      max = x * 2;    // запоминаем левый потомок
    // иначе запоминаем больший потомок из двух
    else if (arr[x * 2] > arr[x * 2 + 1])
      max = x * 2;
    else
      max = x * 2 + 1;
    // если элемент вершины меньше максимального потомка
    if (arr[x] < arr[max]) 
    {
      int temp = arr[x]; // меняем их местами
      arr[x] = arr[max];
      arr[max] = temp;
      x = max;
    }
    else
      done = 1; // пирамида сформирована
  }
}
// Функция сортировки на куче
void heapSort(int *arr, int array_size) 
{
  // Формируем нижний ряд пирамиды
  for (int i = (array_size / 2); i >= 0; i--)
    siftDown(arr, i, array_size - 1);
  // Просеиваем через пирамиду остальные элементы
  for (int i = array_size - 1; i >= 1; i--)
  {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    siftDown(arr, 0, i - 1);
  }
}

int main()
{ 
  
  int min=0,max=100000;
  int x; scanf("%d",&x);
  double n=wtime();
  int a[x];
  // Заполнение массива случайными числами
  for (int i = 0; i<x; i++)
    a[i] = getrand(min, max);
  // Вывод элементов массива до сортировки
  for (int i = 0; i<x; i++)
    printf("%d ", a[i]);
  printf("\n");
  heapSort(a, x); // вызов функции сортировки
  // Вывод элементов массива после сортировки
  for (int i = 0; i<x; i++)
    printf("%d ", a[i]);
  double m=wtime();
  printf("%lf\n",m-n);
  return 0;
}
