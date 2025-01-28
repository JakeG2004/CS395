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
   // Move the smallest disk to the opposite end of the board
   if(n == 1)
   {
      PrintMove(srcRod, auxRod);
      PrintMove(auxRod, dstRod);
      return;
   }

   // Go down to the next smallest disk
   towerOfHanoi(n - 1, srcRod, dstRod, auxRod);   

   // Move the current disk to B
   PrintMove(srcRod, auxRod);

   // Go down to the next smallest disk again (new flavor)
   towerOfHanoi(n - 1, dstRod, srcRod, auxRod);

   // Move the current disk off of B and onto C
   PrintMove(auxRod, dstRod);

   // Smallest disk again
   towerOfHanoi(n - 1, srcRod, dstRod, auxRod);
}

void PrintMove(char A, char B)
{
   printf("Move %c to %c\n", A, B);
}
