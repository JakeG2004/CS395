#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHABET 128
#define TABLE_ROW_LENGTH 16
#define MIN_WRITEABLE 32

void printShiftTable(int table[]);
void HorspoolMatching(char* needle, char* haystack, int needleLen, int haystackLen);
void ShiftTable(char* needle, int needleLen, int table[]);

int main(int argc, char* argv[])
{
   if(argc != 3)
   {
      printf("Improper usage!\n");
      exit(-1);
   }

   char* needle = argv[1];
   char* haystack = argv[2];

   HorspoolMatching(needle, haystack, strlen(needle), strlen(haystack));
}

void HorspoolMatching(char* needle, char* haystack, int needleLen, int haystackLen)
{
   int matches[haystackLen];

   for(int i = 0; i < haystackLen; i++)
   {
      matches[i] = 0;
   }

   int myArr[MAX_ALPHABET];
   ShiftTable(needle, needleLen, myArr);

   printf("%s\n", haystack);
   int i = needleLen - 1;
   while(i <= haystackLen - 1)
   {
      int k = 0;
      while(k < needleLen && needle[needleLen - 1 - k] == haystack[i - k])
      {
         k++;
      }
      if(k == needleLen)
      {
         printf("%*s%s---found\n", i - needleLen + 1, "", needle);
         matches[i] = 1;
      }
      else
      {
         printf("%*s%s\n", i - needleLen + 1, "", needle);
      }

      i += myArr[(unsigned char)(haystack[i])];
   }

   printf("Matches found at locations:");
   for(int i = 0; i < haystackLen; i++)
   {
      if(matches[i] == 0)
      {
         continue;
      }
      printf(" %i", i - 2);
   }

   printf("\n");
}

void ShiftTable(char* needle, int needleLen, int table[])
{
   for(int i = 0; i < MAX_ALPHABET; i++)
   {
      table[i] = needleLen;
   }

   for(int j = 0; j < needleLen - 1; j++)
   {
      table[(unsigned char)needle[j]] = needleLen - 1 - j;
   }

   printShiftTable(table);
}

void printShiftTable(int table[])
{
   int i = 0;
   int start = 0;

   for(start = MIN_WRITEABLE; start < MAX_ALPHABET; start += TABLE_ROW_LENGTH)
   {
      for(i = start; i < start + TABLE_ROW_LENGTH; i++)
      {
         printf("%c\t", i);
      }

      printf("\n");

      for(i = start; i < start + TABLE_ROW_LENGTH; i++)
      {
         printf("%d\t", table[i]);
      }

      printf("\n\n");
   }
}
