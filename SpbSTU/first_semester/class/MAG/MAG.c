#include <stdio.h>
#include <locale.h>
#include <math.h>

#define N 50 

int main(void)
{
	int i, a = 2, prevc=0, b=2,newc=0, k = 1, p = 1,s = 1;
	int A[N];
	setlocale (LC_CTYPE, "Russian");
	printf("%d ", b);
	for (i=0; i<=N; i++)
	{
		A[k]=a;
		b = a * 2 + prevc;
		a = b % 10;
		newc = b / 10;
		prevc = newc;
		if ((prevc==0) && (a==2))
			break;
		printf("%d ", a);
		k++;
		s=s+1;
	}
	printf("Количество символов: %d \n", s);
	for(p=i+1; p>0; p--)
	{
		printf("%i ", A[p]);
	}
	return 0;
}