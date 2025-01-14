/*********************************************
 * Id: gend0188
 * 
 * Find the min distance between two elements of an array
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char* argv[])
{
   if(argc < 3)
   {
      printf("Program must take at leat two arguments!\n");
      exit(-1);
   }

   int minDist = INT_MAX;

   int ARR_SIZE = argc - 1;
   int myArr[ARR_SIZE];

   // Fill int array
   for(int i = 0; i < ARR_SIZE; i++)
   {
      myArr[i] = atoi(argv[i + 1]);
   }

   // Find min distance
   for(int i = 0; i < ARR_SIZE; i++)
   {
      // Set j = i + 1 to optimize
      for(int j = 0; j < ARR_SIZE; j++)
      {
         if(i == j)
         {
            continue;
         }

         // Store myArr[i] - myArr[j] to optimize
         if(abs(myArr[i] - myArr[j]) < minDist)
         {
            minDist = abs(myArr[i] - myArr[j]);
         }
      }
   }

   printf("%d\n", minDist);

   return minDist;
}
