#include <stdio.h>
#include <stdint.h>

int test(int i)
{  

	printf("\n\nrunning test...\n");
int a,b,c;
  a = 3;
  b = 9;

	if(i == 1)
		c+=1;
  asm volatile
  (
    "mod   %[z], %[x], %[y]\n\t"
    : [z] "=r" (c)
    : [x] "r" (a), [y] "r" (b)

  );

	printf("c is:%d\n",c);


  return 0;
} 

int main()
{
	test(1);
}
