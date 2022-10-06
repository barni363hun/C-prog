#include <stdio.h>

int main()
{
  int a;
  printf("a:");
  scanf("%d",&a);
  int b;
  printf("b:");
  scanf("%d",&b);
  a = a+b;
  b = a-b;
  a = a-b;
  printf("a: %d, b: %d",a,b);
  return 0;
}
