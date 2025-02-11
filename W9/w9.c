#include <stdio.h>
#include <stdlib.h>

void SelectionSort(int* arr, int size);
void PrintArr(int* arr, int n);

int main(int argc, char* argv[])
{
   if(argc < 2)
   {
      printf("Improper usage!\n");
      exit(-1);
   }

   int arrSize = argc - 1;
   int* myArr = (int*)malloc(sizeof(int) * arrSize);

   for(int i = 0; i < arrSize; i++)
   {
      sscanf(argv[i + 1], "%i", &(myArr[i]));
      printf("%i ", myArr[i]);
   }

   printf("\n");

   SelectionSort(myArr, arrSize);
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
      
      PrintArr(arr, n);
   }   
}

void PrintArr(int* arr, int n)
{
   for(int i = 0; i < n; i++)
   {
      printf("%i ", arr[i]);
   }

   printf("\n");
}


