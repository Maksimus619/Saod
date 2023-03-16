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

int main()
{
        int x;
	scanf("%d",&x);
	double n=wtime();
        int mass[x], max=0, min=0, max1=100000;
        for(int i = 0; i < x; i++)
        {
                mass[i]= getrand(min, max1);
                if (max<mass[i]){max=mass[i];}
        }
	max++;
	int mass1[max];
        for(int i = 0; i < max; i++)
        {
                mass1[i] = 0;
        }

        for(int i = 0; i < x; i++)
        {
                mass1[mass[i]] += 1;
        }
		double m=wtime();
		printf("%lf \n",m-n);
        return 0;
}


