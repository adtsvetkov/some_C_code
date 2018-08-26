#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stddef.h>
#pragma warning(disable:4996)
#define N 9
#define A 0
#define B 100
#define L 10
void FillFloats (float arr[], int length, float a, float b)
{
	int i;
	for (i=0; i<length; i++)
	{
		arr[i] = (float)(rand() % 100);
	}
}
void PrintFloats(float arr[], int length)
{
	int i;
	printf("\n{");
	for (i=0; i < length-1; i++)
	{
		printf("%.5lf, ", arr[i]);
	}
	printf("%.5lf", arr[i]);
	printf("}\n");
}
void WriteText(char const *filename, float arr[], int length)
{
	int l;
	FILE *f = fopen(filename, "wt"); //открываем файл
	if (f == NULL) 
	{
		printf("Sorry, i can't open this file. ");
	}
	else 
	{
		for (l=0; l<length; l++)
		{
			fprintf(f, "%.1lf ", arr[l]); //записываем значения в файл
		}
	}
	fclose (f); // закрываем файл
}
void WriteBinary (char const *filename, float arr[], int length)
{
	FILE *f = fopen(filename, "wb"); //открываем файл
	if (f == NULL) 
	{
		printf("Sorry, i can't open this file. ");
	}
	else 
	{
		fwrite (arr, sizeof(float), length, f); //записываем значения в файл
	}
	fclose (f); // закрываем файл
}
int main (void)
{
	float C[N];
	FillFloats(C, N, A, B);
	PrintFloats(C, N);
	WriteText("array.txt", C, N);
	WriteBinary("array.bin", C, N);
	return 0;
}