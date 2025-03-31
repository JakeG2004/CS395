#include <stdio.h>
#include <stdlib.h>

void Quicksort(int*, int, int, int size);
int Partition(int*, int, int);
void PrintSubArray(int* A, int size, int low, int high);
void Swap(int* A, int* B);

int main(int argc, char* argv[])
{
   int* myArr = (int*)malloc(sizeof(int) * (argc - 1));

   for(int i = 1; i < argc; i++)
   {
      myArr[i - 1] = atoi(argv[i]);
   }

   Quicksort(myArr, 0, argc - 2, argc - 1); 
  
   PrintSubArray(myArr, argc - 1, 0, argc - 1); 
}

void Quicksort(int* A, int low, int high, int size)
{
   if(low < high)
   {
      // pi is partition index
      int pi = Partition(A, low, high);
      Quicksort(A, low, pi - 1, size); // Sort lower half
      Quicksort(A, pi + 1, high, size); // Sort upper half
      PrintSubArray(A, size, low, high);
   }
}

int Partition(int* A, int low, int high)
{
   int partVal = A[low];
   int i = low;
   int j = high + 1;

   while(1)
   {
      do
      {
         i++;
      } while(A[i] < partVal && A[i] < partVal);

      do
      {
         j--;
      } while(A[j] > partVal && A[j] > partVal);

      if(i >= j)
      {
         break;
      }

      Swap(&(A[i]), &(A[j]));
   }

   Swap(&(A[low]), &(A[j]));

   return j;
}

void PrintSubArray(int* A, int size, int low, int high)
{
   for(int i = 0; i < size; i++)
   {
      if(i == low)
      {
         printf("[");
      }

      printf("%i", A[i]);

      if(i == high || (i == size - 1 && high >= size))
      {
         printf("] ");
      }

      if(i < size - 1)
      {
         printf(" ");
      }
   }

   printf(" \n");
}

void Swap(int* A, int* B)
{
   if(*A != *B)
   {
      *A ^= *B;
      *B ^= *A;
      *A ^= *B;
   }
}
