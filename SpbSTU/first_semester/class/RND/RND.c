#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#pragma warning(disable:4996)
#define N 10
#define A 1
#define B 2
#define L 10
double Random(double a, double b)
{
    a = a + (((double) rand())/(RAND_MAX+1)) * (b-a);
    return a;
}
void FillRandom (double arr[], int size, double a, double b)
{
	int i;
	for (i=0; i<size; i++)
	{
		arr[i] = Random(a, b);
	}
}
void Print(double const arr[], int size)
{
	int i;
	printf("\n{");
	for (i=0; i < size-1; i++)
	{
		printf("%.5lf, ", arr[i]);
	}
	printf("%.5lf", arr[i]);
	printf("}\n");
}
void BuildHistogram(double const arr[], int size, double a, double b, int spans[], int numSpans)
{
	int i, k, n;
	double l;
	for (i=0; i<numSpans; i++)
	{
		spans[i] = 0;
	}
	for (k=0; k<size; k++)
	{
		l = ((arr[k]-a)*numSpans)/(b-a);
		n = (int) l;
		spans[n]++;
	}
}
int TheBiggest(int spans[], int numSpans)
{
	int i, max=0;
	for (i=0; i<numSpans; i++)
	{
		if (spans[i]>spans[max]) max=spans[i];
	}
	return max;
}

void PrintHistogramLine(int value, int width)
{
	int i, k;
	for (i=0; i<value; i++)
	{
		printf("#");
	}
	for (k=value; k<width; k++)
	{
		printf(".");
	}
	printf("\n");
}
void PrintHistogram(int spans[], int numSpans, int width)
{
	int l;
	for (l=0; l<numSpans; l++)
	{
		PrintHistogramLine(spans[l], width);
	}
}
int main(void)
{
    double C[N];
	int K[L];
	setlocale(LC_CTYPE, "Russian"); 
	/*int i;
    srand((unsigned int) time(0));
    for (i = 0; i < 100; ++i)
	printf("¬ведите диапазон случайных чисел: ");
	scanf("%lf %lf", &A, &B);*/
	FillRandom(C, N, A, B);
	Print(C,N);
	BuildHistogram(C, N, A, B, K, L);
	PrintHistogram(K, L, TheBiggest(K, L)+1);
    return 0;
}