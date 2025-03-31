#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void JumbleArrs(int** arrs, int* arrSizes);
void SelectionSort(int* arr, int size);
void InsertionSort(int* A, int arrSize);
void Quicksort(int* A, int low, int high, int size); 
int Partition(int* A, int low, int high);
void Swap(int* A, int* B);

// globals
int smallArrSize = 0;
int medArrSize = 0;
int largeArrSize = 0;

int main(int argc, char* argv[])
{
   int minArrSize = atoi(argv[1]);
   // Set array sizes
   int arrSizes[3];
   arrSizes[0] = minArrSize;
   arrSizes[1] = minArrSize * 10;
   arrSizes[2] = minArrSize * 100;
   
   // Seed rand
   srand(time(NULL));

   // Create arrays
   int** arrs = (int**)malloc(sizeof(int*) * 3);
   for(int i = 0; i < 3; i++)
   {
      arrs[i] = (int*)malloc(sizeof(int) * arrSizes[i]);
   }   

   // Insert arrays
   JumbleArrs(arrs, arrSizes);   

   // Arrays to store times
   float selectionTimes[3];
   float insertionTimes[3];
   float quicksortTimes[3];

   // Time selectionSort
   for(int i = 0; i < 3; i++)
   {
      struct timeval start;
      struct timeval stop; 
      gettimeofday(&start, NULL);
      SelectionSort(arrs[i], arrSizes[i]);
      gettimeofday(&stop, NULL);
   
      selectionTimes[i] = (float)(stop.tv_sec - start.tv_sec) * 1000 + (float)(stop.tv_usec - start.tv_usec) / 1000;
   }

   // Jumble Arrs
   JumbleArrs(arrs, arrSizes);

   for(int i = 0; i < 3; i++)
   {
      struct timeval start;
      struct timeval stop;
      gettimeofday(&start, NULL);
      InsertionSort(arrs[i], arrSizes[i]);
      gettimeofday(&stop, NULL);

      insertionTimes[i] = (float)(stop.tv_sec - start.tv_sec) * 1000 + (float)(stop.tv_usec - start.tv_usec) / 1000;
   }

   // Jumble Arrs
   JumbleArrs(arrs, arrSizes);

   for(int i = 0; i < 3; i++)
   {  
      struct timeval start;
      struct timeval stop; 
      gettimeofday(&start, NULL);
      Quicksort(arrs[i], 0, arrSizes[i] - 1, arrSizes[i]);
      gettimeofday(&stop, NULL);
      
      quicksortTimes[i] = (float)(stop.tv_sec - start.tv_sec) * 1000 + (float)(stop.tv_usec - start.tv_usec) / 1000;
   }

   // Print
   printf("+--------------------+----------------+----------------+-----------+\n");
   printf("| Number of Elements | Selection Sort | Insertion Sort | Quicksort |\n");
   printf("+--------------------+----------------+----------------+-----------+\n");
   for(int i = 0; i < 3; i++)
   {
      printf("| %18d | %14.0f | %14.0f | %9.0f |\n", arrSizes[i], selectionTimes[i], insertionTimes[i], quicksortTimes[i]);   
   }
   printf("+--------------------+----------------+----------------+-----------+\n");

}

void JumbleArrs(int** arrs, int* arrSizes)
{
   // Insert arrays
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < arrSizes[i]; j++)
      {
         arrs[i][j] = rand() % arrSizes[2];
      }
   }
}

void SelectionSort(int* arr, int n)
{
   for(int i = 0; i < n - 1; i++)
   {
      int min_idx = i;

      for(int j = i + 1; j < n; j++)
      {
         if(arr[j] < arr[min_idx])
         {
            min_idx = j;
         }
      }

      int tmp = arr[i];
      arr[i] = arr[min_idx];
      arr[min_idx] = tmp;
   }
}

void InsertionSort(int* A, int arrSize)
{
   // Iterate through each element in the list
   for(int i = 1; i < arrSize; i++)
   {
      // Get the current element
      int curVal = A[i];

      // Get the end of the sorted region
      int sortedIdx = i - 1;

      // Place the element in the sorted list
      while(sortedIdx >= 0 && A[sortedIdx] > curVal)
      {
         A[sortedIdx + 1] = A[sortedIdx];
         sortedIdx--;
      }

      A[sortedIdx + 1] = curVal;
   }
}

void Quicksort(int* A, int low, int high, int size)
{
   if(low < high)
   {
      // pi is partition index
      int pi = Partition(A, low, high);
      Quicksort(A, low, pi - 1, size); // Sort lower half
      Quicksort(A, pi + 1, high, size); // Sort upper half
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
      } while(i <= high && A[i] < partVal);

      do
      {
         j--;
      } while(j >= low && A[j] > partVal);

      if(i >= j)
      {
         break;
      }

      Swap(&(A[i]), &(A[j]));
   }

   Swap(&(A[low]), &(A[j]));

   return j;
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

/*
+--------------------+----------------+----------------+-----------+
| Number of Elements | Selection Sort | Insertion Sort | Quicksort |
+--------------------+----------------+----------------+-----------+
|              10000 |            147 |             82 |         2 |
|             100000 |          14575 |           8265 |        19 |
|            1000000 |        1458924 |         827281 |       217 |
+--------------------+----------------+----------------+-----------+
*/
