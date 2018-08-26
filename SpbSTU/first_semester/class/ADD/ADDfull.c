#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define LENGTH 9 //в задании указано 10, но int не может превышать 10 символов, поэтому контроль работает некорректно
int max_length;
int fill(int number, int digits[], int length) 
{
    int i = 0, p = 0, kek;
    kek = number;
    while (kek != 0) 
	{
        kek = kek / 10;
        p++;
    }
	if (p>length)
	{
		printf("Sorry, number of characters is more than allowed :( \n");
		exit(0);
	}
    for (i = 0; i < length; i++) 
	{
        digits[i] = number % 10;
        number = number / 10;
    }
    return p;
}

void print(int digits[], int length) 
{
    int i, p;
    for (p = length - 1; p > 0; p--)
	{
        if (digits[p] != 0) break;
	}
    for (i = 1; i < length - p; i++)
	{
		printf("  ");
	}
    for (i = p; i >= 0; i--)
	{
        printf("%i ", digits[i]);
	}
    printf("\n");
}

void Add(int x[], int xLength, int y[], int yLength, int xy[], int xyLength) 
{
    int k, preva = 0;
    for (k = 0; k < xyLength - 1; k++) 
	{
        xy[k] = (x[k] + y[k]) % 10 + preva;
        preva = (x[k] + y[k]) / 10;
    }
    if (preva == 0) max_length--;
    else xy[k] = preva;
}

int Collect(int digits[], int length) 
{
    int i = 1, p;
    int z = 0;
    for (p = 0; p <= length - 1; p++) 
	{
        z = z + digits[p] * i;
        i = i * 10;
    }
    return z;
}

int main(void) 
{
    int a, b, d, e, i;
    int B[LENGTH], A[LENGTH], C[LENGTH + 1];
    scanf("%i %i", &a, &b);
    d = fill(a, A, LENGTH);
    e = fill(b, B, LENGTH);
    if (d >= e) max_length = d + 1;
    else max_length = e + 1;
    Add(A, d, B, e, C, max_length);
    print(A, max_length);
    print(B, max_length);
    for (i = 0; i < max_length-1; i++)
	{
	printf("--");
	}
    printf("-\n");
    print(C, max_length);
    printf("Calc result: %u \n", a + b);
    printf("Collect result: %u ", Collect(C, max_length));
    return 0;
}