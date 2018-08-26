#include <stdio.h>
#include <locale.h>
#pragma warning(disable:4996)
#define N 9
void Fill(int arr[], int size)
{
	int i = 0;
	for (i; i<size; i++)
	{
		arr[i]=i+1;
	}
}
void Print(int arr[], int size)
{
	int i = 0;
	for (i; i<size; i++)
	{
		printf("%i", arr[i]);
	}
	printf("\n");
}
void Shift1(int arr[], int size)
{
	int i, c;
	c=arr[0]; // ���������� ������ �������, ����� ��������� ��� � �����
	for (i=0; i < size; i++) //� ������� �� ������������� ������� �������
	{
		arr[i] = arr[i+1]; //������ ���������� ������, ������� ������ ������
	}
	arr[size-1] = c;//������� ����������� �������
}
/*void Shift_Ver1(int arr[], int size, int delta)
{
	int i = 0, l = 0, m=0, n=0, p=0, B[N];
	if (delta > N) delta = delta % N;
	for (p; p < delta; p++) //���������� ������ delta ���������, ����� ����� ��������� �� � �����
	{
		B[p] = arr[p];
	}
	for (l = delta; l < size; l++) //��������� ��������� size - delta ��������� � ������
	{
		arr[m]=arr[l];
		m++;
	}
	for (i; i < delta; i++) //��������� ������ delta ��������� � �����
	{
		arr[size - delta+n] = B[i];
		n++;
	}
}*/
void Shift_Ver1(int arr[], int size, int delta)
{
	int i=0;
	if (delta > N) delta = delta % N;
	for (i; i < delta; i++)
	{
		Shift1(arr, size);
	}
}

void Reverse (int arr[], int left, int right)
{
	int seredina, m, B[N]; 
	int l = 0, n = 0, p, r=0;
	seredina = (right - left)/2 +1;
	for (m = left; m <=right; m++) //���������� ��� �������� �� ����� ������� �� ������
	{
		B[n] = arr[m];
		n++;
	}
	for (p = right; p >= left; p--) //����������� ��������� ������� �� ����� ������� �� ������ �������� ������� B[ ] � �����
	{
		arr[p] = B[r];
		r++;
	}
}
/*void Shift_Ver2(int arr[], int size, int delta)
{
	int C[N], D[N], i=0;
	int k=0, z=0;
	for (i=0; i < delta; i++)
	{
		C[i] = arr [i];
		k++;
	}
	for (i; i<size; i++)
	{
		D[i] = arr [i];
		z++;
	}
	Print(C, k);
	printf(" | ");
	Print(D, z);
}*/
void Shift_Ver2(int arr[], int sdvig)
{
	if (sdvig > N) sdvig = sdvig % N;
	Reverse(arr, 0, N-1);
	Reverse(arr, 0, N-1-sdvig);
	Reverse(arr, N-sdvig, N-1);
}
int main(void)
{
	int A[N], DEL, SDVIG;
	setlocale(LC_CTYPE, "Russian"); 
	Fill(A, N);
	printf("�������� ������: ");
	Print(A, N);
	/*Shift1(A, N);
	printf("����� �� ������� �����: ");
	Print(A, N);*/
	printf("������� �����: ");
	scanf("%i", &DEL);
	Shift_Ver1 (A, N, DEL);
	printf("C����� 1: ");
	Print(A, N);
	Fill(A, N);
	printf("������� �����: ");
	scanf("%i", &SDVIG); 
	printf("C����� 2: ");
	Shift_Ver2(A, SDVIG);
	Print(A, N);
	return 0;
}