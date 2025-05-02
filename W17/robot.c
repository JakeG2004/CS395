#include <stdio.h>
#include <stdlib.h>

void FixBoard(int width, int height, int** values);
int** ConvertToArr(int width, int height, char* argv[]);
void PrintBoard(int width, int height, int** board);
int IsAccessible(int width, int height, int y, int x, int** values);
int CalculateCoinValue(int width, int height, int y, int x, int** values, int** coinBoard);
int** GetCoinBoard(int width, int height, int** values);

int main(int argc, char* argv[])
{
   if(argc < 3)
   {
      printf("Invalid Usage!\n");
      exit(-1);
   }

   int height = atoi(argv[1]);
   int width = atoi(argv[2]);

   if(argc - 3 != width * height)
   {
      printf("Invalid number of args!\n");
      exit(-1);
   }

   int** values = ConvertToArr(width, height, argv);
   
   printf("Board Inputed:\n");
   PrintBoard(width, height, values);
   FixBoard(width, height, values);
   int** coinBoard = GetCoinBoard(width, height, values);

   printf("\nCoin Collecting Table:\n");
   PrintBoard(width, height, coinBoard);

   printf("\nThe optimal path with this board is: %i\n", coinBoard[height - 1][width - 1]);
}

void FixBoard(int width, int height, int** values)
{
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         if(!IsAccessible(width, height, i, j, values))
         {
            values[i][j] = -1;
         }
      }
   }
}

int** GetCoinBoard(int width, int height, int** values)
{
   int** coinBoard = (int**)malloc(sizeof(int*) * height);

   for(int i = 0; i < height; i++)
   {
      coinBoard[i] = (int*)malloc(sizeof(int) * width);

      for(int j = 0; j < width; j++)
      {
         coinBoard[i][j] = CalculateCoinValue(width, height, i, j, values, coinBoard); 
      }
   }

   return coinBoard;
}

int CalculateCoinValue(int width, int height, int y, int x, int** values, int** coinBoard)
{
   if(values[y][x] == -1)
   {
      return 0;
   }

   if(y == 0 && x == 0)
   {
      return 0;
   }

   if(y == 0)
   {
      return coinBoard[y][x - 1] + values[y][x];
   }

   if(x == 0)
   {
      return coinBoard[y - 1][x] + values[y][x];
   }

   int upperVal = coinBoard[y - 1][x];
   int leftVal = coinBoard[y][x - 1];

   return(upperVal > leftVal ? upperVal + values[y][x] : leftVal + values[y][x]);
}

int IsAccessible(int width, int height, int y, int x, int** values)
{
   // Handle origin
   if(y == 0 && x == 0)
   {
      return 1;
   }

   // Handle top row
   if(y == 0)
   {
      return values[y][x - 1] != -1;
   }

   // Handle left column
   if(x == 0)
   {
      return values[y - 1][x] != -1;
   }

   // Handle other cases
   if(values[y - 1][x] == -1 && values[y][x - 1] == -1)
   {
      return 0;
   }

   return 1;
}

int** ConvertToArr(int width, int height, char* argv[])
{
   int** values = (int**)malloc(sizeof(int*) * height);
   for (int i = 0; i < height; i++) 
   {
      values[i] = (int*)malloc(sizeof(int) * width);
   }

   for (int i = 0; i < height; i++) 
   {
      for (int j = 0; j < width; j++) 
      {
         if(argv[3 + (i * width) + j][0] == 'X')
         {
            values[i][j] = -1;
         }

         else
         {
            values[i][j] = atoi(argv[3 + (i * width) + j]);
         }
      }
   }

   return values;
}

void PrintBoard(int width, int height, int** board)
{
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
                    if (board[i][j] == -1)
            {
                printf("X  "); // X is a single character, so add two spaces
            }
            else
            {
                if (board[i][j] < 10)
                    printf("%d  ", board[i][j]);  // 1-digit number + 2 spaces
                else
                    printf("%d ", board[i][j]);   // 2-digit number + 1 space
            } 
      }

      printf("\n");
   }
}
