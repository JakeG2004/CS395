#include <stdio.h>
#include <stdlib.h>

void Permutations(int n, int dig, int used, int num);

int main(int argc, char* argv[])
{
   if(argc != 2)
   {
      printf("Invalid Usage!\n");
      exit(-1);
   }

   int n = 0;
   for(int i = 0; argv[1][i] != '\0'; i++)
   {
      n += argv[1][i] - '0';

      if(argv[1][i + 1] != '\0')
      {
         n *= 10;
      }
   }

   Permutations(n, 0, 0, 0);
}

void Permutations(int n, int dig, int used, int num)
{
   if(dig == n)
   {
      printf("%0*d\n", n, num);
      return;
   }

   for(int i = 1; i <= n; i++)
   {
      if(!(used & (1 << i)))
      {
         Permutations(n, dig + 1, used | (1 << i), num * 10 + i);
      }
   }
}
