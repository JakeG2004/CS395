/*********************************************
 * Id: gend0188
 * 
 * Gaussian Elimination
 *********************************************/ 
#include <stdio.h>
#include <stdlib.h>


void GaussianElimination(float** matrix, int dimension);
void PrintMatrix(int dimension, float** matrix);
float** CreateMatrix(int argc, char* argv[]);

int main(int argc, char* argv[])
{
   // Check for correct number of arguments
   if(argc < 3)
   {
      printf("Invalid Input! ./a.out <number of rows> <content of rows>\n");
      exit(-1);
   }

   // Get teh number of rows
   int numRows = atoi(argv[1]);
   int numCols = numRows + 1;

   // Check for the correct number of values
   if((argc - 2) != numRows * numCols)
   {
      printf("Invalid Input! Need number of entries = first argument * (first argument + 1)\n");
      exit(-1);
   }

   float** matrix = CreateMatrix(argc, argv);

   GaussianElimination(matrix, numRows);
}

// Perform Gaussian Eliminaton on the matrix
void GaussianElimination(float** matrix, int dimension)
{
   PrintMatrix(dimension, matrix);

   for(int i = 0; i < dimension - 1; i++)
   {
      for(int j = i + 1; j < dimension; j++)
      {
         float tempji = matrix[j][i];
         for(int k = i; k < dimension + 1; k++)
         {
            matrix[j][k] = matrix[j][k] - (matrix[i][k] * tempji / matrix[i][i]);
         }
      }
      PrintMatrix(dimension, matrix);
   }
}

// Create the matrix given the arguments
float** CreateMatrix(int argc, char* argv[])
{
   // Get the number of rows
   int numRows = atoi(argv[1]);
   int numCols = numRows + 1;

   // Dynamically create empty 2D matrix
   float** matrix = (float**)malloc(sizeof(float*) * numRows);
   for(int i = 0; i < numRows; i++)
   {
      matrix[i] = (float*)malloc(sizeof(float) * numCols);
   }

   // Populate matrix
   int curIndex = 0;
   for(int i = 0; i < numRows; i++)
   {
      for(int j = 0; j < numCols; j++)
      {
         matrix[i][j] = atof(argv[curIndex + 2]);
         curIndex++;
      }
   }

   return matrix;
}

// Print a matrix given an array and a dimension
void PrintMatrix(int dimension, float** matrix)
{
   for(int i = 0; i < dimension; i++)
   {
      for(int j = 0; j < dimension + 1; j++)
      {
         printf("%.2f ", matrix[i][j]);
      }

      printf("\n");
   }
   printf("\n");
}
