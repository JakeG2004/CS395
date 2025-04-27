#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHABET 128
#define TABLE_ROW_LENGTH 16
#define MIN_WRITEABLE 32

void printShiftTable(int table[]);
void HorspoolMatching(char* needle, char* haystack, int needleLen, int haystackLen);
void ShiftTable(char* needle, int needleLen, int table[]);
void GoodSuffixTable(char* needle, int needleLen, int table[]);

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

   int goodArr[haystackLen + 1];
   for(int i = 0; i < haystackLen + 1; i++)
   {
      goodArr[i] = 0;
   }
   GoodSuffixTable(needle, needleLen, goodArr);

   printf("%s\n", haystack);
   int i = needleLen - 1;
   while(i <= haystackLen - 1)
   {
      int k = 0;
      int d1 = myArr[(unsigned char)(haystack[i])] - k;
      if(d1 < 1)
      {
         d1 = 1;
      }
      int d2 = goodArr[haystack[i]];

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
         printf("%*s%s d1=%d d2=%d\n", i - needleLen + 1, "", needle, d1, d2);
      }

      int shift = 0;
      if(k == 0)
      {
         shift = d1;
      }

      if(needleLen > k && k > 0)
      {
         if(d1 > d2)
         {
            shift = d1;
         }
         else
         {
            shift = d2;
         }
      }
      if(k == needleLen)
      {
         shift = 1;
      }

      i += shift;
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

void GoodSuffixTable(char* needle, int needleLen, int table[]) 
{
    // Initialize all entries to 0
    for(int i = 0; i <= needleLen; i++) {
        table[i] = 0;
    }

    int bpos[needleLen + 1];
    int i = needleLen;
    int j = needleLen + 1;
    bpos[i] = j;

    while(i > 0) {
        while(j <= needleLen && needle[i-1] != needle[j-1]) {
            if(table[j] == 0) {
                table[j] = j - i;
            }
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j;
    }

    // Second pass for prefixes
    j = bpos[0];
    for(i = 0; i <= needleLen; i++) {
        if(table[i] == 0) {
            table[i] = j;
         }
      if(i == j) {
         j = bpos[j];
      }
   }

   // Swap the array
   int tmp[needleLen + 1];
   for(int i = 0; i < needleLen + 1; i++)
   {
      tmp[i] = table[needleLen - i];
   }

   for(int i = 0; i < needleLen + 1; i++)
   {
      table[i] = tmp[i];
   }
   
   for(int i = 1; i < needleLen; i++)
   {
      printf("%d %*s %d\n", i, needleLen, &(needle[needleLen - i]), table[i]);
   } 
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
