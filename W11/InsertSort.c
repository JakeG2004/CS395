#include <stdio.h>
#include <stdlib.h>

void printArr(int* A, int arrSize, int curPos);
void InsertionSort(int** A, int arrSize);

int main(int argc, char* argv[])
{
   // Ensure proper usage
   if(argc < 3)
   {
      printf("Invalid Usage...\n");
      exit(-1);
   }

   // Malloc for the array
   int arrSize = argc - 1;
   int* myArr = (int*)malloc(sizeof(int) * arrSize);
   if(myArr == NULL)
   {
      printf("Failed to malloc...\n");
      exit(-1);
   }

   // Assign the array
   for(int i = 1; i <= arrSize; i++)
   {
      myArr[i - 1] = atoi(argv[i]);
   }

   InsertionSort(&myArr, arrSize);
}

void InsertionSort(int** A, int arrSize)
{
   printArr(*A, arrSize, 1);

   // Iterate through each element in the list
   for(int i = 1; i < arrSize; i++)
   {
      // Get the current element
      int curVal = (*A)[i];
      
      // Get the end of the sorted region
      int sortedIdx = i - 1;

      // Place the element in the sorted list
      while(sortedIdx >= 0 && (*A)[sortedIdx] > curVal)
      {
         (*A)[sortedIdx + 1] = (*A)[sortedIdx];
         sortedIdx--;
      }

      (*A)[sortedIdx + 1] = curVal;
      printArr(*A, arrSize, i + 1);
   } 
}

void printArr(int* A, int arrSize, int curPos)
{
   for(int i = 0; i < arrSize; i++)
   {
      if(i == curPos)
      {
         printf("| ");
      }
      printf("%i ", A[i]);

      if(i == arrSize - 1 && curPos == arrSize)
      {
         printf("| ");
      }
   }

   printf("\n");
}
