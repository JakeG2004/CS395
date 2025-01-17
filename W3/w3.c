/*********************************************
 * Id: gend0188
 * 
 * Brute force method to find 2^n.
 * w03
 *********************************************/


#include <stdio.h>
#include <stdlib.h>

int PowN(int n);

int main(int argc, char* argv[])
{
    // Validate arguments
    if(argc != 2)
    {
        printf("ERROR: Need 1 argument!\n");
        exit(-1);
    }

    int n = atoi(argv[1]);

    int res = PowN(n);
    
    printf("%i\n", res);
}

int PowN(int n)
{
    if(n <= 0)
    {
        return 1;
    }

    return(PowN(n - 1) + PowN(n - 1));
}