/*********************************************
 * Id: gend0188
 * 
 * Tower of Hanoi
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

void towerOfHanoi(int n, char srcRod, char dstRod, char auxRod);

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

// Calculate moves for Tower of Hanoi given post names and number of disks. Recursive
void towerOfHanoi(int n, char srcRod, char dstRod, char auxRod)
{
   // Base case
   if(n == 1)
   {
      printf("Move %c to %c\n", srcRod, dstRod);
      return;
   }

   // Rest of process
   towerOfHanoi(n-1, srcRod, auxRod, dstRod);
   printf("Move %c to %c\n", srcRod, dstRod);
   towerOfHanoi(n-1, auxRod, dstRod, srcRod);
}
