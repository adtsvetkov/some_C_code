/* STR-5 task */
#pragma warning(disable:4996) 
#include <stdio.h> 
#include <locale.h> 
void SwapCase(char str[]) 
{ 
int i; 
for (i = 0;i< strlen(str); i++) 
{ 
if (str[i] >= 65 && str[i] <= 90) 
str[i] += 32; 
else if (str[i] >= 97 && str[i] <= 122) 
str[i] -= 32; 
printf("%c", str[i]); 
} 
} 
int main(void) 
{ 
char a[100]; 
setlocale(LC_ALL, "Russian"); 
do 
{ 
printf("¬ведите строку\n"); 
fgets(a, 100, stdin); 
SwapCase(a); 
} while (strlen(a) != 1); 
return 0; 
}