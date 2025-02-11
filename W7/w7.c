/*********************************************
 * Id: gend0188
 * 
 * Tower of Hanoi
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

void towerOfHanoi(int n, char srcRod, char dstRod, char auxRod);
void PrintMove(char A, char B);

int main(int argc, char* argv[])
{
   // Ensure correct num arguments
   if(argc != 2)
   {
      printf("Usage: ./a.out <number of disks>\n");
      exit(-1);
   }

   // Get numnber of disks
   int numDisks = atoi(argv[1]);

   // Start function
   towerOfHanoi(numDisks, 'A', 'C', 'B');
}

void towerOfHanoi(int n, char srcRod, char dstRod, char auxRod)
{
   if(n == 0)
   {
      return;
   }

   char* validMoves = "ABC";

   int dist = 2;

   for(int i = 0; validMoves[i] != '\0'; i++)
   {
      if(validMoves[i] == srcRod && validMoves[(i + 1) % 3] == dstRod)
      {
         dist = 1;
         break;
      }
   }

   // This is an issue after disk n has moved once. It only goes to A when it should go to B
   if(dist == 2)
   {
      towerOfHanoi(n - 1, srcRod, dstRod, auxRod);
      
      PrintMove(srcRod, auxRod);

      towerOfHanoi(n - 1, dstRod, srcRod, auxRod);

      PrintMove(auxRod, dstRod);

      towerOfHanoi(n - 1, srcRod, dstRod, auxRod);
   }

   if(dist == 1)
   {
      towerOfHanoi(n - 1, srcRod, auxRod, dstRod);
      
      PrintMove(srcRod, dstRod);

      towerOfHanoi(n - 1, auxRod, dstRod, srcRod);
   }

}


void PrintMove(char A, char B)
{
   printf("Move %c to %c\n", A, B);
}
