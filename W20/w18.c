#include <stdio.h>
#include <stdlib.h>

int** MakeAdjMatrix(int dimension, char* argv[]);
void PrintMatrix(int** matrix, int dimension);
int IsEmpty(int* arr, int arrSize);
int* RemoveElement(int* arr, int elementToRemove, int arrSize);
void BronKerbosch(int* R, int rSize, int* P, int pSize, int* X, int xSize, int** adjMatrix, int dimension, int* cliques);
int* Neighbors(int v, int** arr, int dimension, int* neighborCount);
int* Union(int* arr, int newElement, int arrSize, int* newSize);
int* Intersect(int* arr1, int* arr2, int nArr1, int nArr2, int* resultSize);

int main(int argc, char* argv[])
{
   if(argc < 2)
   {
      printf("Invaliud!\n");
      exit(-1);
   }

   int dimension = atoi(argv[1]);

   int** adjMatrix = MakeAdjMatrix(dimension, argv);

   PrintMatrix(adjMatrix, dimension);

   int* R = NULL;
   int* P = (int*)malloc(sizeof(int) * dimension);
   for(int i = 0; i < dimension; i++)
   {
      P[i] = i;
   }

   int* X = NULL;
   int* cliques = (int*)malloc(sizeof(int) * dimension);
   for(int i = 0; i < dimension; i++)
   {
      cliques[i] = 0;
   }
   BronKerbosch(R, 0, P, dimension, X, 0, adjMatrix, dimension, cliques);
   for(int i = dimension; i >= 0; i--)
   {
      if(cliques[i] == 0)
      {
         printf("No clique found of size %i\n", i);
         continue;
      }

      printf("Clique found of size %i\n", i);
      exit(0);
   }
}

void BronKerbosch(int* R, int rSize, int* P, int pSize, int* X, int xSize, int** adjMatrix, int dimension, int* cliques)
{
   /*
   if(P is empty and X is empty) then
      report R as a maximal clique
   foreach vertex v in P
      BronKerbosch(R union {v}, P intersect N(v), X intersect N(v))
      P = P \ {v}
      X = X Union {v}
   */

   if(pSize == 0 && xSize == 0)
   {
      cliques[rSize] = 1;
   }

   for(int i = 0; i < pSize; i++)
   {
      int v = P[i];

      int neighborCount = 0;
      int* neighbors = Neighbors(v, adjMatrix, dimension, &neighborCount);

      int tmpRSize = rSize;
      int* tmpR = Union(R, v, rSize, &tmpRSize);
 
      int tmpPSize = 0;
      int* tmpP = Intersect(P, neighbors, pSize, neighborCount, &tmpPSize);

      int tmpXSize = 0;
      int* tmpX = Intersect(X, neighbors, xSize, neighborCount, &tmpXSize);

      BronKerbosch(tmpR, tmpRSize, tmpP, tmpPSize, tmpX, tmpXSize, adjMatrix, dimension, cliques);
      P = RemoveElement(P, v, pSize);
      pSize--;
      X = Union(X, v, xSize, &xSize);
   }
}

// Get the list of neighbors for a given node
int* Neighbors(int v, int** arr, int dimension, int* neighborCount)
{
   int* neighbors = (int*)malloc(sizeof(int) * dimension);
   int count = 0;

   for(int i = 0; i < dimension; i++)
   {
      if(arr[v][i] == 1)
      {
         neighbors[count++] = i;
      }
   }

   *neighborCount = count;
   return neighbors;
}

int* Intersect(int* arr1, int* arr2, int nArr1, int nArr2, int* resultSize)
{
   if(arr1 == NULL || arr2 == NULL)
   {
      return NULL;
   }

   int* result = (int*)malloc(sizeof(int) * (nArr1 < nArr2 ? nArr1 : nArr2));
   for(int i = 0; i < nArr1; i++)
   {
      for(int j = 0; j < nArr2; j++)
      {
         if(arr1[i] == arr2[j])
         {
            result[*resultSize] = arr1[i];
            (*resultSize)++;
         }
      }
   }

   //result = (int*)realloc((void*)result, (*resultSize));
   return result;
}

int* RemoveElement(int* arr, int elementToRemove, int arrSize)
{
   if(arr == NULL || arrSize == 0)
   {
      return arr;
   }

   if(arrSize == 1)
   {
      return NULL;
   }

   // If last element is not the element to remove, overwrite then shrink
   if(arr[arrSize - 1] != elementToRemove)
   {
      for(int i = 0; i < arrSize; i++)
      {
         if(arr[i] == elementToRemove)
         {
            arr[i] = arr[arrSize - 1];
            arr = (int*)realloc((void*)arr, sizeof(int) * (arrSize - 1));
            return arr;
         }
      }
   }

   arr = (int*)realloc((void*)arr, arrSize - 1);
   return arr;
}

int* Union(int* arr, int newElement, int arrSize, int* newSize)
{
   // Check for duplicates
   for(int i = 0; i < arrSize; i++)
   {
      if(arr[i] == newElement)
      {
         return arr;
      }
   }

   // Add it to the list
   arr = (int*)realloc((void*)arr, sizeof(int) * (arrSize + 1));
   arr[arrSize] = newElement;
   (*newSize)++;

   return arr;
}

int IsEmpty(int* arr, int arrSize)
{
   for(int i = 0; i < arrSize; i++)
   {
      if(arr[i] != -1)
      {
         return 0;
      }
   }

   return 1;
}

int** MakeAdjMatrix(int dimension, char* argv[])
{
   int** matrix = (int**)malloc(sizeof(int*) * dimension);
   
   for(int i = 0; i < dimension; i++)
   {
      matrix[i] = (int*)malloc(sizeof(int) * dimension);
   }

   int curIndex = 2;
   for(int i = 0; i < dimension; i++)
   {
      for(int j = i; j < dimension; j++)
      {
         if(i == j)
         {
            matrix[i][j] = 0;
            continue;
         }

         matrix[i][j] = atoi(argv[curIndex]);
         matrix[j][i] = atoi(argv[curIndex]);

         curIndex++;
      }
   }

   return matrix;
}

void PrintMatrix(int** matrix, int dimension)
{
   for(int i = 0; i < dimension; i++)
   {
      for(int j = 0; j < dimension; j++)
      {
         printf("%i ", matrix[i][j]);
      }

      printf("\n");
   }
}
