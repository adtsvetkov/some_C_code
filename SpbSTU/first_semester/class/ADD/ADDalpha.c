#include <stdio.h>
#include <locale.h>

#define LENGTH 10

#pragma warning(disable:4996)

void fill(int number, int digits[], int length)
{
	int i=0, p=1, kek;
	kek=number;
	while (kek != 0)
	{
		kek = kek/10;
		p++;
	}
	if (p > LENGTH)
	{
		printf("Sorry, number of characters is more than 10 :( \n");
		digits[LENGTH]={0};
		return;
	}
	while (number>0)
	{
		for (i=0; i<length; i++)
		{
			digits[i]=number % 10;
            number=number / 10;
		}
	}
}
void print (int digits[], int length)
{
	int p;
	for(p=length-1; p>=0; p--)
	{
		if (digits[p] == 0)
		continue;
		printf("%i ", digits[p]);
	}
}
int main(void)
{
	int a, b, B[LENGTH], A[LENGTH];
	scanf("%i %i", &a, &b);
	fill(a, A, LENGTH);
	fill(b, B, LENGTH);
	print(A, LENGTH);
	printf("\n");
	print(B, LENGTH);
	return 0;
}