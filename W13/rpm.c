#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void RussianPeasantMult(int num1, int num2);

int main(int argc, char* argv[])
{
   if(argc != 3)
   {
      printf("Improper usage!\n");
      exit(-1);
   }

   int num1 = atoi(argv[1]);
   int num2 = atoi(argv[2]);

   RussianPeasantMult(num1, num2);
}

void RussianPeasantMult(int num1, int num2)
{
   int sum = 0;

   // Do the multiplication
   while(num1 >= 1)
   {
      // Handle num1 being odd
      if(num1 % 2 == 1)
      {
         printf("%6d %6d %6d\n", num1, num2, num2);
         sum += num2;
      }

      // num1 is even
      else
      {
         printf("%6d %6d\n", num1, num2);
      }

      // Scale the numbers
      num2 *= 2;
      num1 = (int)floor(num1 / 2);
   }

   // Print results
   printf("%20s\n", "------");
   printf("%20d\n", sum);
}
