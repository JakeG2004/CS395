#include <stdio.h>
#include <stdlib.h>

int BruteForceStringMatch(char* inString, char* pattern);
int myStrnCmp(char* str1, char* str2, int n);

int main(int argc, char* argv[])
{
   if(argc != 3)
   {
      printf("ERROR: Usage is ./a.out <pattern> <teststring>\n");
   }
   BruteForceStringMatch(argv[2], argv[1]); 
}

int BruteForceStringMatch(char* inString, char* pattern)
{
   int inSize = 0;
   int patSize = 0;

   int matches = 0;

   for(int i = 0; inString[i] != '\0'; i++)
   {
      inSize++;
   }

   for(int i = 0; pattern[i] != '\0'; i++)
   {
      patSize++;
   }

   printf("Matches found at locations: ");
   
   for(int i = 0; i <= inSize - patSize; i++)
   {
      if(myStrnCmp(&(inString[i]), pattern, patSize))
      {
         if(matches > 0)
         {
            printf(" ");
         }
         printf("%i", i);
         matches++;
      }
   }

   printf("\n");

   if(matches == 0)
   {
      return -1;
   }

   return matches;
}

int myStrnCmp(char* str1, char* str2, int n)
{
   for(int i = 0; i < n; i++)
   {
      if(str1[i] != str2[i])
      {
         return 0;
      }
   }

   return 1;
}
