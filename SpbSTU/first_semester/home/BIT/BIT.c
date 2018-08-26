/*BIT-1 task*/

#include <stdio.h>
#include <math.h>
#include <locale.h>
#pragma warning (disable:4996)
typedef unsigned long long MaxInt;
typedef unsigned char integer_t;
//typedef unsigned short integer_t;
//typedef unsigned int integer_t;
//typedef unsigned long integer_t;
//typedef unsigned long long integer_t;
integer_t bits_reverse(integer_t i) 
{
  integer_t r = 0;
  int l;
  for(l=0; l< (sizeof(integer_t)*8); l++) 
  {
    r = (r << 1) + (i & 1); //сдвигаем нулевое число на один бит влево, кладем туда первый бит числа i
	i >>= 1; //сдвигаем исходное число на единицу вправо, чтобы считать следующий бит
  }
  return r;
}
void in_binary(integer_t n)
{
	int l;
	for (l=sizeof(integer_t)*8-1; l >= 0; l--)
	{
		printf("%i",(1 & (n >> l))); //узнаем и выводим lый бит числа n: сдвигаем на l единиц число n вправо, используем логическое "и" дл€ битов (см. таблицу истинности)
	}
} 
integer_t Len(integer_t a, integer_t b)
{
	integer_t k=0;
	if (a>b)
	{
		while (a!=0)
		{
			a = a / 10;
			k++;
		}
	}
	else 
	{
		while (b!=0)
		{
			b = b / 10;
			k++;
		}
	}
	return k;
}
void Print(integer_t n, integer_t length)
{
	MaxInt k;
	int l;
	k = (MaxInt) n;
	l = (int) length;
	printf("%*llu = 0x%0*llx = ", l, k, sizeof(integer_t) * 2, k);
	in_binary(n);
	printf("\n");
}
int main (void)
{
	MaxInt k;
	integer_t l, rev, len;
	do
	{
		setlocale(LC_ALL, "Russian");
		printf("¬ведите число: ");
		scanf("%llu", &k);
		l = (integer_t) k;
		rev = bits_reverse(l);
		len = Len(l, rev);
		printf("¬ы ввели  : ");
		Print(l, len);
		printf("–езультат : ");
		Print(rev, len);
	}
	while (k!=0);
	return 0;
}