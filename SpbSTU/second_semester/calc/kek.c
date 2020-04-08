// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#define _USE_MATH_DEFINES
#include <stdlib.h> 
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#pragma  warning(disable: 4996)
#include <malloc.h>
#include <string.h>
#include <windows.h>
#define eps 0.0000000001
typedef struct
{
	char *mas;
	int size;
	int memoryerr;
} str_arr;
typedef struct
{
	str_arr ans;
	int err;
} str_array;
typedef struct
{
	double ans;
	int err;
	int memoryerr;
} calc;
int IsSpace(char k)
{
	if ((k==' ') || (k == '\t') || (k=='\n') || (k == '\v') || (k == '\f') || (k=='\r')) return 0;
	else return -1;
}
void Vnikuda (void)
{
	int b;
	do
	{
		b=getchar();
	} while ((b!='\n') && (b!=EOF));
}
calc Calculate (str_arr kek)
{
	calc result; /*возвращает структуру с ответом ans и проверкой на ошибку*/
	double *stack;
	double acc=1;
	double *q;
	char *endptr;
	size_t i=0;
	result.ans = 0;
	result.err = -1;
	result.memoryerr = 0;
	endptr = kek.mas;
	stack = (double *) malloc(sizeof(double));
	if (stack == NULL)
	{
		result.memoryerr = -1;
		return result;
	}
	while (*endptr!='\0')
	{
		if ((*endptr>='0') && (*endptr<='9'))
		{
			stack[i] = strtod(endptr, &endptr);
			i++;
			q = realloc(stack, (i+1)*sizeof(double));
			if (q == NULL)
			{
				result.memoryerr = -1;
				free(stack);
				return result;
			}
			else stack = q;
		}
		if (*endptr == 'e')
		{
			stack[i] = M_E;
			i++;
			q = realloc(stack, (i+1)*sizeof(double));
			if (q == NULL)
			{
				result.memoryerr = -1;
				free(stack);
				return result;
			}
			else stack = q;
		}
		if (*endptr == '!')
		{
			stack[i] = M_PI;
			i++;
			q = realloc(stack, (i+1)*sizeof(double));
			if (q == NULL)
			{
				result.memoryerr = -1;
				free(stack);
				return result;
			}
			else stack = q;
		}
		if (*endptr == '*')
		{
			stack[i-2] = (stack[i-1]*stack[i-2]);
			stack[i-1] = 1;
			i--;
		}
		if (*endptr == '+')
		{
			stack[i-2] = stack[i-1] + stack[i-2];
			stack[i-1] = 0;
			i--;
		}
		if (*endptr == '/')
		{
			if ((stack[i-1]>0) || (stack[i-1]<0))
			{
				stack[i-2] = stack[i-2] / stack[i-1];
				stack[i-1] = 1;
				i--;
			}
			else 
			{
				free(stack);
				return result;
			}
		}
		if (*endptr == '-')
		{
			stack[i-2] = stack[i-2] - stack[i-1];
			stack[i-1] = 0;
			i--;
		}
		if (*endptr == '^')
		{
			if ((stack[i-2]<0) && ((fmod(stack[i-1], 1)>0) || (fmod(stack[i-1], 1)<0)))
				{
					free(stack);
					return result;
			}
			else
			{
				stack[i-2] = pow(stack[i-2], stack[i-1]);
				stack[i-1] = 1;
				i--;
			}
		}
		if (*endptr == '?')
		{
			if (stack[i-1] >= 0) stack[i-1] = sqrt(stack[i-1]);
			else 
				{
					free(stack);
					return result;
			}
		}
		if (*endptr == '#') 
		{
			if (fabs(sin(stack[i-1]))<eps) stack[i-1] = 0;
			else stack[i-1] = sin(stack[i-1]);
		}
		if (*endptr == '&') 
		{
			if ((fabs(cos(stack[i-1])))<eps) stack[i-1] = 0;
			else stack[i-1] = cos(stack[i-1]);
		}
		if (*endptr == '{')
		{
			if (fabs(cos(stack[i-1])) < eps) acc=0;
			if ((acc<0) || (acc>0))
			{
				if ((fabs(sin(stack[i-1])))<eps) stack[i-1] = 0;
				else stack[i-1] = tan(stack[i-1]);
			}
			else
				{
					free(stack);
					return result;
			}
		}
		if (*endptr == '}')
		{
			if (fabs(sin(stack[i-1])) < eps) acc=0;
			if ((acc<0) || (acc>0))
			{
				if ((fabs(cos(stack[i-1])))<eps) stack[i-1] = 0;
				else stack[i-1] = 1/tan(stack[i-1]);
			}
			else 
				{
					free(stack);
					return result;
			}
		}
		if (*endptr == ':')
		{
			if ((stack[i-1]>=-1) && (stack[i-1]<=1)) stack[i-1] = asin(stack[i-1]);
			else 
				{
					free(stack);
					return result;
			}
		}
		if (*endptr == ';')
		{
			if ((stack[i-1]>=-1) && (stack[i-1]<=1)) stack[i-1] = acos(stack[i-1]);
			else 
				{
					free(stack);
					return result;
			}
		}
		if (*endptr == '$') stack[i-1] = atan(stack[i-1]);
		if (*endptr == '<') 
		{
			if (stack[i-1] > 0) stack[i-1] = log(stack[i-1]);
			else 
				{
					free(stack);
					return result;
			}
		}
		if (*endptr == '>') stack[i-1] = floor(stack[i-1]);
		if (*endptr == '@') 
		{
			stack[i-1] = ceil(stack[i-1]);
			//if (stack[i-1] == -0) stack[i-1] = 0;
		}
		endptr++;
	}
	result.ans = stack[i-1];
	result.err = 0;
	free(stack);
	free(kek.mas);
	return result;
}
int UniOrNot (char k) //если унарный, то 1, если бинарный, 2, если не символ операции, 0
{
	if ((k == '?') || (k == '#') || (k == '&') || (k == '{') || (k == '}') || (k == ':') || (k == ';') || (k == '$') || (k == '<') || (k == '>') || (k == '@')) return 1;
	if ((k == '*') || (k == '/') || (k == '+') || (k == '-') || (k == '^')) return 2;
	return 0;
}
int InvalidExpression (const char *a, size_t size)
{
	//размер вместе с '\0'
	size_t i;
	for (i=0; i<(size_t) size; i++)
	{
		if (a[i] == '!')
		{
			//cмотрим справа
			if (!((a[i+1] == ')') || (UniOrNot(a[i+1]) == 2) || (i+2==(size_t) size))) return -1;
			//cмотрим слева
			if (!((a[i-1] == '(') || (UniOrNot(a[i-1]) != 0) || (i==0))) return -1;
		}
		if (UniOrNot(a[i]) == 1)
		{
			//cправа
			if (!((a[i+1] == '(') || (a[i+1] == 'e') || (a[i+1] == '!') || (a[i+1] == '-') || (UniOrNot(a[i+1])!=0) || ((a[i+1]>='0') && (a[i+1]<='9')))) return -1;
			//слева
			if (!((a[i-1] == '(') || (UniOrNot(a[i-1]) != 0) || (i==0))) return -1;
		}
		if ((UniOrNot(a[i]) == 2) && (a[i]!= '-'))
		{
			//cправа
			if (!(((a[i+1]>='0') && (a[i+1]<='9')) || (a[i+1] == 'e') || (a[i+1] == '!') || (UniOrNot(a[i+1])==1) || (a[i+1] == '-') || (a[i+1] == '('))) return -1;
			//cлева
			if (!(((a[i-1]>='0') && (a[i-1]<='9')) || (a[i-1] == 'e')  || ((a[i] == '+') && (a[i-1] == 'E') && (a[i-2]>='0') && (a[i-2]<='9')) || (a[i-1] == '!') || (a[i-1] == ')'))) return -1;
		}
		if (a[i] == '(')
		{
			//cправа
			if (!((a[i+1] == '-') || ((a[i+1]>='0') && (a[i+1]<='9')) || (a[i+1] == 'e') || (a[i+1] == '!') || (a[i+1] == '(') || (UniOrNot(a[i+1])==1))) return -1;
			//cлева
			if (!((UniOrNot(a[i-1])!=0) || (a[i-1] == '(') || (i==0))) return -1;
		}
		if (a[i] == ')')
		{
			//cлева
			if (!(((a[i-1]>='0') && (a[i-1]<='9')) || (a[i-1] == 'e') || (a[i-1] == '!') || (a[i-1] == ')'))) return -1;
			//cправа
			if (!((UniOrNot(a[i+1])==2) || (a[i+1] == ')') || (i+2==(size_t) size))) return -1;
		}
		if (a[i] == '-')
		{
			//cправа
			if (!((a[i+1] == '-') || ((a[i+1]>='0') && (a[i+1]<='9')) || (a[i+1] == 'e') || (a[i+1] == '!') || (a[i+1] == '(') || (UniOrNot(a[i+1])==1))) return -1;
			//cлева
			if (!((UniOrNot(a[i-1])!=0) || (i==0) || ((a[i-1]>='0') && (a[i-1]<='9')) || (a[i-1] == 'e') || (a[i-1] == '!') || (a[i-1] == ')') || (a[i-1] == '(') || ((a[i-1] == 'E') && (a[i-2]>='0') && (a[i-2]<='9')))) return -1;
		}
	}
	return 0;
}
str_array FuncTransition(const char *a, size_t size) //маллочит новый массив, ничего не освобождает
{
	char *arr;
	char *q;
	size_t acc=0;
	size_t i=0, k=0;
	str_array arrr;
	arrr.err = 0;
	arrr.ans.memoryerr = 0;
	arr = (char *) malloc((k+1)*sizeof(char));
	if (arr == NULL)
	{
		arrr.ans.memoryerr = -1;
		return arrr;
	}
	for (i=0; i<(size_t) size; i++)
	{
		if ((a[i]>='a') && (a[i]<='z'))
		{
			if ((a[i] == 'p') && (a[i+1] == 'i')) //pi
			{
				arr[k] = '!';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i++;
				acc++;
			}
			if ((a[i] == 's') && (a[i+1] == 'q') && (a[i+2] == 'r') && (a[i+3] == 't')) //sqrt
			{
				arr[k] = '?';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i+=3;
				acc++;
			}
			if ((a[i] == 's') && (a[i+1] == 'i') && (a[i+2] == 'n')) //sin
			{
				arr[k] = '#';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i+=2;
				acc++;
			}
			if ((a[i] == 'c') && (a[i+1] == 'o') && (a[i+2] == 's')) //cos
			{
				arr[k] = '&';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i+=2;
				acc++;
			}
			if ((a[i] == 't') && (a[i+1] == 'g')) //tg
			{
				arr[k] = '{';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i++;
				acc++;
			}
			if ((a[i] == 'c') && (a[i+1] == 't') && (a[i+2] == 'g')) //ctg
			{
				arr[k] = '}';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i+=2;
				acc++;
			}
			if ((a[i] == 'a') && (a[i+1] == 'r') && (a[i+2] == 'c') && (a[i+3] == 's') && (a[i+3+1] == 'i') && (a[i+5] == 'n')) //arcsin
			{
				arr[k] = ':';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i+=5;
				acc++;
			}
			if ((a[i] == 'a') && (a[i+1] == 'r') && (a[i+2] == 'c') && (a[i+3] == 'c') && (a[i+3+1] == 'o') && (a[i+5] == 's')) //arccos
			{
				arr[k] = ';';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i+=5;
				acc++;
			}
			if ((a[i] == 'a') && (a[i+1] == 'r') && (a[i+2] == 'c') && (a[i+3] == 't') && (a[i+3+1] == 'g')) //arctg
			{
				arr[k] = '$';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i=i+3+1;
				acc++;
			}
			if ((a[i] == 'l') && (a[i+1] == 'n')) //ln
			{
				arr[k] = '<';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i++;
				acc++;
			}
			if ((a[i] == 'f') && (a[i+1] == 'l') && (a[i+2] == 'o') && (a[i+3] == 'o') && (a[i+3+1] == 'r')) //floor
			{
				arr[k] = '>';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i=i+3+1;
				acc++;
			}
			if ((a[i] == 'c') && (a[i+1] == 'e') && (a[i+2] == 'i') && (a[i+3] == 'l')) //ceil
			{
				arr[k] = '@';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				i+=3;
				acc++;
			}
			if (a[i] == 'e') //e
			{
				arr[k] = 'e';
				k++;
				q = realloc (arr, (k+1)*sizeof(char));
				if (q == NULL)
				{
					arrr.ans.memoryerr = -1;
					free(arr);
					return arrr;
				}
				else arr=q;
				acc++;
			}
			if (acc == 0)
			{
				arrr.err = -1;
				free(arr);
				return arrr;
			}
		}
		if (((a[i]>='z') || (a[i]<='a')) && (isspace(a[i]) == 0))
		{
			arr[k] = a[i];
			k++;
			q = realloc (arr, (k+1)*sizeof(char));
			if (q == NULL)
			{
				arrr.ans.memoryerr = -1;
				free(arr);
				return arrr;
			}
			else arr=q;
		}
		acc=0;
	}
	arr[k] = '\0';
	arrr.ans.mas = arr;
	arrr.ans.size = (int)k+1;
	return arrr;
}
int SymbolsOrIncorrectBrackets(const char *a, size_t size)
{
	size_t i, k=0, l=0, m=0;
	char acc;
	for (i=0; i<(size_t)size; i++)
	{
		acc = a[i];
		if (((acc<'0')||(acc>'9')) && (acc!='(') && (acc!='.') && (acc!=')') && (acc!='^') && (acc!='*') && (acc!='/') && (acc != '+') && (acc != '-') && (IsSpace(acc) == -1) && (acc!='\n') && (acc!='e') && (acc!='s') && (acc!='q') && (acc!='r') && (acc!='t') && (acc!='i') && (acc!='n') && (acc!='c') && (acc!='o') && (acc!='g') && (acc!='a') && (acc!='l') && (acc!='f') && (acc!='E') && (acc!='p') && (acc!=-1)) k++;
		if (acc == '(') l++;
		if (acc == ')') m++;
	}
	if ((k==0) && (l==m)) return 0;
	else return -1;
}
int SpaceSymbols(const char *a, size_t size)
{
	size_t acc=0;
	size_t acc2=0;
	size_t i, l;
	int k;
	for (i=0; i<(size_t)size; i++)
	{
		if ((a[i]>='0') && (a[i]<='9'))
		{
			if ((a[i-1] >= '0') && (a[i-1]<='9')) acc++; //цифры
			if ((a[i-1] == 's') || (a[i-1] == 'g') || (a[i-1] == 'n') || (a[i-1] == 'r') || (a[i-1] == 'l') || (a[i-1] == 't') || (i==0)) acc++; //знак унарной операции
			if (((a[i-1] == '-') && ((a[i-2] == 'e') || (a[i-2] == 'E')) && ((a[i-3]>='0') && (a[i-3]<='9'))) || ((a[i-1] == '+') && ((a[i-2] == 'e') || (a[i-2] == 'E')) && ((a[i-3]>='0') && (a[i-3]<='9'))) || (((a[i-1] == 'e') || (a[i-1] == 'E')) && ((a[i-2]>='0') && (a[i-2]<='9')))) acc++; //научна€ запись
			if (a[i-1] == '.') acc++; //точка
			if ((UniOrNot(a[i-1]) == 2) && !(((a[i-2] == 'e') || (a[i-2] == 'E')) && ((a[i-3]>='0') && (a[i-3]<='9'))) || (a[i-1] == '(')) acc++; //знаки бинарных операций и скобки
			if (i>=1) //пробелы слева
			{
				if (!(isspace(a[i-1])==0))
				{
					k= (int) i;
					do
					{
						k--;
					}while ((k>=0) && (isspace(a[(size_t)k])!= 0));
					if ((a[(size_t)k] == '(') || (UniOrNot(a[(size_t)k]) == 2) || (k+1 == 0)) acc++;
				}
			}
			if (acc == 1) acc = 0;
			else return 0;
			if (a[i+1] == -1) acc++;
			if ((a[i+1] >= '0') && (a[i+1]<='9')) acc++; //цифры
			if (((a[i+1] == 'e') || (a[i+1] == 'E')) && (((a[i+2] == '-') && (a[i+3] >='0') && (a[i+3]<='9')) || ((a[i+2] == '+') && (a[i+3] >='0') && (a[i+3]<='9')) || ((a[i+2] >='0') && (a[i+2]<='9')))) acc++;
			if (a[i+1] == '.') acc++; //точка
			if ((UniOrNot(a[i+1]) == 2) || (a[i+1] == ')')) acc++; //знаки бинарных операций и скобки
			if (!(isspace(a[i+1])==0))
			{
				k=(int)i;
				do
				{
					l=(size_t)k;
					l++;
				} while ((l<size-1) && (isspace(a[l])!= 0));
				k=(int)l;
				if ((a[(size_t)k] == ')') || (UniOrNot(a[(size_t)k]) == 2) || (k+1 == (int) size) || (a[(size_t)k] == -1)) acc++;
			}
			//if ((i==0) && (acc==0)) acc++;
			if (acc == 1) acc = 0;
			else return 0;
		}
		if (a[i] == 'E')
		{
			if (((a[i-1] >= '0') && (a[i-1]<='9')) && (((a[i+1]>='0') && (a[i+1]<='9')) || ((a[i+1] == '-') && (a[i+2]>='0') && (a[i+2]<='9')) || ((a[i+1] == '+') && (a[i+2]>='0') && (a[i+2]<='9')))) 
			{
				//справа
				if ((a[i+1] == '-') || (a[i+1] == '+')) k=i+1;
				else k=i;
				do
				{
					k++;
				} while ((k<(int)size-1) && ((a[k]>='0') && (a[k]<='9')));
				if ((a[k] == ')') || (UniOrNot(a[k]) == 2) || (k+1 == (int) size) || (isspace(a[k])!=0)) acc2++;
				if (acc2 == 0) return 0;
				else acc2 = 0;
				//cлева
				k=i;
				do
				{
					k--;
				}while ((k>=0) && (((a[k]>='0') && (a[k]<='9')) || (a[k] == '.')));
				if ((a[k] == '(') || (UniOrNot(a[k]) == 2) || (k+1 == 0) || (isspace(a[k])!=0)) acc2++;
				//printf("left = %i\n", acc2);
				if (acc2 == 0) return 0;
				else acc2 = 0;
			}
			else return 0;
		}
		if (a[i] == 'e')
		{
			if (((a[i-1] >= '0') && (a[i-1]<='9')) && (((a[i+1]>='0') && (a[i+1]<='9')) || ((a[i+1] == '-') && (a[i+2]>='0') && (a[i+2]<='9')) || ((a[i+1] == '+') && (a[i+2]>='0') && (a[i+2]<='9'))))
			{
				//справа
				/*k=i;
				do
				{
				k++;
				}while ((k<size-1) && (((a[k]>='0') && (a[k]<='9')) || (a[k] == '-') || (a[k] == '+')));
				if ((a[k] == ')') || (UniOrNot(a[k]) == 2) || (k+1 == size) || (isspace(a[k])!=0) || (a[k] == '.') || (a[k] =='E') || (a[k] == 'e')) acc2++;
				if (acc2 == 0) return 0;
				else acc2 = 0;*/
				if ((a[i+1] == '-') || (a[i+1] == '+')) k=i+1;
				else k=i;
				do
				{
					k++;
				}while ((k<(int) size-1) && ((a[k]>='0') && (a[k]<='9')));
				if ((a[k] == ')') || (UniOrNot(a[k]) == 2) || (k+1 == (int) size) || (isspace(a[k])!=0)) acc2++;
				if (acc2 == 0) return 0;
				else acc2 = 0;
				//cлева
				k=i;
				do
				{
					k--;
				}while ((k>=0) && (((a[k]>='0') && (a[k]<='9')) || (a[k] == '.')));
				if ((a[k] == '(') || (UniOrNot(a[k]) == 2) || (k+1 == 0) || (isspace(a[k])!=0)) acc2++;
				if (acc2 == 0) return 0;
				else acc2 = 0;
			}
			else
			{
				//pomogite
				if ((a[i-1] == 'c') && (a[i+1] == 'i')) acc2++;
				//смотрим слева
				if ((a[i-1] == 's') || (a[i-1] == 'g') || (a[i-1] == 'n') || (a[i-1] == 'r') || (a[i-1] == 'l') || (a[i-1] == 't') || (i==0)) acc2++;
				if ((UniOrNot(a[i-1]) == 2) || (a[i-1] == '(')) acc2++;
				if (i>=1)
				{
					if (!(isspace(a[i-1])==0))
					{
						k=i;
						do
						{
							k--;
						}while ((k>=0) && (isspace(a[k])!= 0));
						if ((a[k] == '(') || (UniOrNot(a[k]) == 2) || (k+1 == 0)) acc2++;
					}
				}
				if (acc2 == 0) return 0;
				if (acc2 == 1) acc2 = 0;
				//смотрим справа
				if ((a[i-1] == 'c') && (a[i+1] == 'i')) acc2++;
				if ((UniOrNot(a[i+1]) == 2) || (a[i+1] == ')')) acc2++;
				if (!(isspace(a[i+1])==0))
				{
					k=i;
					do
					{
						k++;
					}while ((k< (int) size-1) && (isspace(a[k])!= 0));
					if ((a[k] == ')') || (UniOrNot(a[k]) == 2) || (k+1 == (int) size)) acc2++;
				}
				if (acc2 == 0) return 0;
				if (acc2 == 1) acc2 = 0;
			}
		}
		if (a[i] == '.')
		{
			if ((a[i-1]>='0') && (a[i-1]<='9') && (a[i+1]>='0') && (a[i+1]<='9'))
			{
				//справа
				k=i;
				do
				{
					k++;
				} while ((k<(int)size-1) && (a[k]>='0') && (a[k]<='9'));
				if ((a[k] == ')') || (UniOrNot(a[k]) == 2) || (k+1 == (int) size) || (isspace(a[k])!=0) || (a[k] == 'E') || (a[k] == 'e')) acc2++;
				if (acc2 == 0) return 0;
				else acc2 = 0;
				//cлева
				k=i;
				do
				{
					k--;
				}while ((k>=0) && (a[k]>='0') && (a[k]<='9'));
				if ((a[k] == '(') || (UniOrNot(a[k]) == 2) || (k+1 == 0) || (isspace(a[k])!=0)) acc2++;
				if (((a[k-1] == 'E') || (a[k-1] == 'e')) && ((a[k] == '-') || (a[k] == '+')) && (a[k-2]>='0') && (a[k-2]<='9')) return 0;
				if (acc2 == 0) return 0;
				else acc2 = 0;
			}
			else return 0;
		}
	}
	return 1;
}
int OpPriority(char k)
{
	if ((k == '?') || (k == '#') || (k == '&') || (k == '{') || (k == '}') || (k == ':') || (k == ';') || (k == '$') || (k == '<') || (k == '>') || (k == '@')) return 6;
	if (k == '^') return 5;
	if ((k == '*') || (k == '/')) return (3+1);
	if ((k == '+') || (k == '-')) return 3;
	if (k == '(') return 2;
	if (k == ')') return 1;
	return 0;
}
str_arr ReversePolishNotation(char *a, size_t size) //маллочит стэк и аутпут, освобождает только стэк
{
	char *stack, *output;
	str_arr arr;
	int p1, p2=0; /*k - счетчик элементов выходной строки, l - счетчик элементов стэка*/
	size_t i, k=0, l=0;
	int z;
	char *q;
	arr.memoryerr = 0;
	stack = (char *)malloc(sizeof(char));
	if (stack == NULL)
	{
		arr.memoryerr = -1;
		return arr;
	}
	output = (char *)malloc(sizeof(char));
	if (output == NULL)
	{
		free(stack);
		arr.memoryerr = -1;
		return arr;
	}
	for(i=0; i<(size_t)size; i++)
	{
		if (a[i] == 'e')
		{
			if (((a[i-1]>='0') && (a[i-1]<='9')) && (((a[i+1]>='0') && (a[i+1]<='9')) || (((a[i+1] == '-') || (a[i+1] == '+')) && ((a[i+2]>='0') && (a[i+2]<='9')))))
			{
				output[k]=a[i];
				k++;
				q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
			}
			else
			{
				output[k]=a[i];
				k++;
				q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
				output[k] = ' ';
				k++;
				q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
			}
		}
		if (a[i] == 'E')
		{
			output[k]=a[i];
			k++;
			q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
		}
		if (a[i] == '!') 
		{
			output[k]=a[i];
			k++;
			q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
			output[k] = ' ';
			k++;
			q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
		}
		if ((a[i]>='0') && (a[i]<='9') || (a[i] == '.')) /*если цифра или разделитель, просто помещаем в выходную строку, перевыдел€ем пам€ть*/
		{
			output[k]=a[i];
			k++;
			q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
			if (((a[i+1]<'0') || (a[i+1]>'9')) && (a[i+1] != '.') && (a[i+1] != 'e') && (a[i+1] != 'E')) /*если следующий знак не точка, нe e и не цифра, ставим пробел*/
			{
				output[k] = ' ';
				k++;
				q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
			}
		}
		if ((a[i] == '-') && ((a[i-1] != '!') && (a[i-1]!=')') && (a[i-1] != 'e') && (a[i-1]!= 'E') && ((a[i-1]<'0') || (a[i-1]>'9')) || ((i-1)<0)))
		{
			stack[l] = a[i];
			l++;
			q = realloc(stack, (l+1)*sizeof(char));
			if (q == NULL) 
			{
				free(output);
				arr.memoryerr = -1;
				return arr;
			}
			else stack=q;
			output[k]='0';
			k++;
			q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
			output[k] = ' ';
			k++;
			q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
		}
		if (((a[i] == '-') || (a[i] == '+')) && ((a[i-1] == 'e') || (a[i-1] == 'E')) && ((a[i-2] >='0') && (a[i-2]<='9')))
		{
			output[k]=a[i];
			k++;
			q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
		}
		if ((a[i] == '*') || (a[i] == '/') || (((a[i] == '+') || ((a[i] == '-') && !((a[i] == '-') && (a[i-1]!=')') && ((a[i-1] != '!') && (a[i-1] != 'e') && (a[i-1]!= 'E') && ((a[i-1]<'0') || (a[i-1]>'9')) || ((i-1)<0))))) && !(((a[i-1] == 'e') || (a[i-1] == 'E')) && ((a[i-2] >='0') && (a[i-2]<='9')))) || (a[i] == '^') || (a[i] == '(') || (a[i] == '?') || (a[i] == '#') || (a[i] == '&') || (a[i] == '{') || (a[i] == '}') || (a[i] == ':') || (a[i] == ';') || (a[i] == '$') || (a[i] == '<') || (a[i] == '>') || (a[i] == '@')) /*если символ, делаем кучу проверок*/
		{
			p1 = OpPriority(a[i]); /*смотрим на приоритетность введенного символа*/
			if (l!=0)
			{
				p2 = OpPriority(stack[l-1]); /*приоритет последнего символа на стеке*/
			}
			if ((l==0) || (p2<p1) || (p1==2) || ((p1 == 5) && (p2 == 5)) || ((p1 == 6) && (p2 == 6))) /*если стек пуст, или приоритет последнего ниже, чем введенный, или это скобка, помещаем в стек*/
			{
				stack[l] = a[i];
				l++;
				q = realloc(stack, (l+1)*sizeof(char));
			if (q == NULL) 
			{
				free(output);
				arr.memoryerr = -1;
				return arr;
			}
			else stack=q;
			}
			if ((p1<=p2) && (p1!=2) && !((p1 == 5) && (p2 == 5)) && !((p1 == 6) && (p2 == 6))) /*если последний приоритет на стеке больше чем введенный символ, вытаскиваем все, пока не будет меньше*/
			{
				do 
				{
					output[k] = stack[l-1];
					k++;
					q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
					l--;
				} while (p1<=OpPriority(stack[l-1]));
				stack[l] = a[i];
				l++;
			}
			p2=0;
		}
		if (a[i] == ')')
		{
			while ((stack[l-1]!='(') && (l!=0))
			{
				output[k] = stack[l-1];
				k++;
				q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
				l--;
			}
			if (l==0)
			{
				arr.mas = NULL;
				arr.size = -1;
				return arr;
			}
			l--;
		}
	}
	for(z=(int)l-1; z>=0; z--)
	{
		output[k] = stack[(size_t)z];
		k++;
		q = realloc(output, (k+1)*sizeof(char));
				if (q == NULL) 
				{
					free(stack);
					arr.memoryerr = -1;
					return arr;
				}
				else output=q;
	}
	free(stack);
	output[k] = '\0';
	arr.mas = output;
	arr.size = (int) k;
	free(a);
	/*for (i=0; i<k; i++)
	{
	if((output[i] == '#') || (output[i] == ':') || (output[i] == '&') || (output[i] == '}') || (output[i] == '!') || (output[i] == '>') || (output[i] == '?'))
	{
	if (output[i] == '#') printf("sin");
	if (output[i] == ':') printf("arcsin");
	if (output[i] == '&') printf("cos");
	if (output[i] == '}') printf("ctg");
	if (output[i] == '!') printf("pi");
	if (output[i] == '>') printf("floor");
	if (output[i] == '?') printf("sqrt");
	}
	else printf("%c", output[i]);
	}*/
	return arr;
}
int PreCalculate (const char *a, size_t size)
{
	str_array arr;
	calc arr_end;
	str_arr arr1;
	printf(" == ");
	if(SymbolsOrIncorrectBrackets(a, size) == 0) 
	{
		if (SpaceSymbols (a, size) == 1)
		{
			arr = FuncTransition(a, size);
			if (arr.ans.memoryerr == 0)
			{
				if (arr.err == 0)
				{
					if (InvalidExpression(arr.ans.mas, (size_t) arr.ans.size) == 0)
					{
						arr1 = ReversePolishNotation(arr.ans.mas, (size_t) arr.ans.size);
						if (arr1.memoryerr == 0)
						{
							if (arr1.size>0) 
							{
								arr_end = Calculate(arr1);
								if (arr_end.memoryerr == 0)
								{
									if (arr_end.err == 0)
									{
										printf("%g", arr_end.ans);
									}
									else printf("ERROR: troubles with expression");
								}
								else return -1;
							}
							if (arr1.size== 0) printf("ERROR: empty string.");
							if (arr1.size<0) printf("ERROR: incorrect brackets.");
						}
						else return -1;
					}
					else printf("ERROR: expression is invalid.");
				}
				else printf("ERROR: incorrect string."); 
			}
			else return -1;
		} 
		else printf("ERROR: incorrect space symbols or operands.");
	}
	else printf("ERROR: incorrect string. There were not enough brackets or incorrect symbols found.");
	printf("\n");
	return 0;
}
int IsACommentString(char *a, size_t size)
{
	size_t i, n, k=0;
	for(i=0; i<size; i++)
	{
		if ((a[i] == '/') && (a[i+1] == '/'))
		{
			for (n=0; n<i; n++)
			{
				if (!(a[n]<0)) if (!isspace(a[n]) == 0) k++;
			}
			if (k==i) return 1;
			else return 0;
		}
	}
	return 0;
}
int StringTreatment(void)
{
	size_t s=0, i, k=0, com;
	char *q;
	char b;
	int acc;
	char *arr;
	acc = getc(stdin);
	if (acc != EOF)
	{
		b = (char)acc;
		if (b!='\n')
		{
			arr = (char *)malloc(sizeof(char));
			if (arr == NULL)
			{
				Vnikuda();
				return -1;
			}
			do
			{
				if (s != 0)
				{
					acc = getc(stdin);
					arr[s] = (char) acc;
				}
				else arr[s] = b;
				if (!(arr[s]<0)) if (!isspace((int)arr[s]) == 0) k++;
				s++;
				q = realloc(arr, (s+1)*sizeof(char));
				if (q == NULL)
				{
					if (acc!= '\n') Vnikuda();
					return -1;
				}
				else arr=q;
				b = arr[s-1];
			} 
			while ((b!='\n') && (acc!=EOF));
			com = IsACommentString(arr, s);
			for (i=0; i<s-1; i++)
			{
				printf("%c", arr[i]);
			}
			if ((com==0) && (k!=s)) 
			{
				if (PreCalculate(arr, s) == -1) return -1;
			}
			if ((com == 1) || (k==s)) printf("\n");	
			free(arr);
		}
		else printf("\n");
	}
	return 0;
} 
int main(int argc, char const* argv[]) 
{
	FILE *f;
	int str;
	SetConsoleCP(1251); //установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); //установка кодовой страницы win-cp 1251 в поток вывода
	if (argc>2) 
	{
		printf("ERROR: Too much arguments. \n"); /*обрабатываем случай с бќльшим количеством аргументов*/
		return -1;
	}
	else {
		if (argc==2)
		{
			f = freopen(argv[1], "r", stdin);    /*открываем файл в поток*/
			if (f == NULL) 
			{
				printf("ERROR: File does not exist. \n"); /*обрабатываем случай, когда файл не удалось открыть*/
				return -1; 
			}
		}
		do 
		{
			str = StringTreatment();
			if (stdout == NULL)
			{
				printf("ERROR: cannot read the string. \n");
			}
			if (str == -1) printf("ERROR: memory allocating failed. \n");
		}while (feof(stdin) == 0);
		fclose(stdout);
	}
	return 0;
}