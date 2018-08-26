#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 3
#pragma warning(disable:4996)
double f(double x)
{
	double sum, k;
	int i=1;
	k=x*x;
	sum=k;
	/*printf("u = %le s = %le\n", k, sum); */
	while (sum!=k+sum)
	 {
		k=k*((-4*x*x)/((2*i+1)*(2*i+2)));
		sum=sum+k;
		/*printf("u = %le s = %le\n", k, sum); */
		i++;
	}
	return sum;
}
double g(double x)
{
	double k, m;
	m=sin(x);
	k=m*m;
	return k;
}
void PrintTable (double a, double b, int m)
{
	int i=0;
	double x;
	printf("+-----+-----------+----------+----------+-------------+\n");
	printf("|  i  |     x     |   f(x)   |   g(x)   |  f(x)-g(x)  |\n");
	printf("+-----+-----------+----------+----------+-------------+\n");
	for (i; i<m; i++)
	{
		x=a+((b-a)/(m-1))*i;
		printf("| %-3i | %9.5lf | %lf | %lf | %11.3le |\n", i, x, f(x), g(x), f(x)-g(x));
	}
	printf("+-----+-----------+----------+----------+-------------+\n");
}
int main(void)
{
	double A, B;
	int M;
	scanf("%lf %lf %i", &A, &B, &M);
	if ((A>=-1) & (A<=1) & (A<=B) & (B>=-1) & (B<=1) & (M>1))
	{
		PrintTable(A, B, M);
	}
	else 
	{
		printf("Sorry, input numbers are incorrect :c ");
		exit(0);
	}
	/*double X, a, b, delta;
	scanf("%lf", &X);
	a=f(X);
	b=g(X);
	delta = a-b;
	printf("x = %lf f = %lf g = %lf delta = %le", X, a, b, delta); */
	return 0;
}
