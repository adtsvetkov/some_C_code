#include <stdio.h>
#include <malloc.h>
#define N 9
#define RUN 600

void FillInt(int a[], int size)
{
	int i, k = RUN;
	for (i = 0; i < size; i++)
	{
		a[i] = k;
		k += 2;
	}
}
void FillDouble(double a[], int size)
{
	int i, k = RUN;
	for (i = 0; i < size; i++)
	{
		a[i] = k;
		k += 2;
	}
}


void PrintInt(int a[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%i ", a[i]);
	printf("\n");
}
void PrintDouble(double a[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%f ", a[i]);
	printf("\n");
}

void MemoryDump(void * ptr, int size)
{
  unsigned char* p = (unsigned char*)ptr;
	int i, j, k; 
	for(i = 0; i < size/16 ; i++)
	{
		printf("%p : ", p); 
		for(j = 0; j < 16; j++)
		{
			printf("%02x ", *p);
			p ++;
		}
		printf("\n");
  } 


	//название последнего блока памяти
	printf("%p : ", p);

  for(k = 0; k < size%16; k++)
    {
      printf("%02x ", *p);
      p ++;
    }

  printf("\n");
}

int main(void)
{
	int a[N], size;
	double b[N];
	
	FillInt(a, N); //указатель на начало массива есть его название
	FillDouble(b, N);
	PrintInt(a, N);
	PrintDouble(b, N);
	size = sizeof(a);
	MemoryDump(a, size);
	size = sizeof(b);
	MemoryDump(b, size);
	return 0;
}