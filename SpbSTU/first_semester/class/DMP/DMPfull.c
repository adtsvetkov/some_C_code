#include <stdio.h>
#pragma warning (disable:4996)
#define N 8
#define bites 16
void FillInt(int a[], int size)
{
int i, K=600;
for (i=0; i<size; i++)
{
a[i] = K;
K += 2;
}
}
void FillDouble (double a[], int size)
{
int i;
double K=600;
for (i=0; i<size; i++)
{
a[i]=K;
K+=2;
}
}
void PrintInt(int a[], int size)
{
int i;
for (i=0; i<size; i++)
{
printf("%i ", a[i]);
}
printf("\n");
}
void PrintDouble (double a[], int size)
{
int i;
for (i=0; i<size; i++)
{
printf("%lf ", a[i]);
}
printf("\n");
}
void MemoryDump (void const* ptr, int size)
{
int i, dl, k, m=0, bit;
unsigned char *p;
p = (unsigned char *) ptr;
bit = bites;
if (size % bites !=0) dl = (size / bites) + 1;
else dl = (size / bites);
for (k = 0; k<dl; k++)
{
printf("%p : ", p);
for (i=m; i<bit; i++)
{
printf("%02x ", *p);
p++;
}
printf("\n");
m+=bites;
if ((size - bit) / 16 > 0) bit+=bites;
else bit += (size - bit);
}
}
int main (void)
{
int A[N], a, b;
double B[N];
FillInt(A, N);
FillDouble(B, N);
PrintInt(A, N);
PrintDouble(B, N);
a = sizeof(A);
b = sizeof (B);
MemoryDump(A, a);
printf("\n");
MemoryDump(B, b);
return 0;
}