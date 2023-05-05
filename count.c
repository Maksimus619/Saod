#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double wtime()
{
struct timeval t;
gettimeofday(&t, NULL);
return (double)t.tv_sec + (double)t.tv_usec * 1E-6; // 1E-6 служит для возведение в -6 степень (*10^-6), а функция получает время в микросекундах и при возврате переводит их в секунды с точностью до миллисекунд
}

int getrand(int min, int max) // функция для генерации случайных чисел в заданном диапазоне min и max
{
return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main()
{
        int x;
	scanf("%d",&x); // считываем
	double n = wtime(); // присваем переменной n значение полученное из wtime
        int mass[x], max=0, min=0, max1=100000;
        for(int i = 0; i < x; i++)
        {
                mass[i]= getrand(min, max1); // генерация случайних чисел для заполнения массива и нахождения максимального значенич
                if (max<mass[i]){max=mass[i];}
        }

	for(int i = 0; i < x; i++)
        {
                printf("%d\n", mass[i]); // вывод до
        }

	max++;
	int mass1[max];
        for(int i = 0, j = 0; i < max; i++)
        {
		while (mass1[i]--){
		mass[j++] = i;
		}
        }

        for(int i = 0; i < x; i++)
        {
                printf("%d\n", mass[i]); // вывод после
        }
 		double m=wtime(); // получение конечного времени выполнения программы
		printf("%lf \n",m-n);
        return 0;
}
