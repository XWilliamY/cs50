#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void encode(char uncyphered[], int k)
{
    int strlength = strlen(uncyphered);
    char cyphered;
    for(int i = 0; i < strlength; i++)
    {
        if(isalpha(uncyphered[i]))
        {
            if(isupper(uncyphered[i]))
            {
                // Finding the distance from cyphered letter
                // To 'A'
                // And then adding that distance to 'A'             
                cyphered = 'A' + (uncyphered[i] + k - 'A')%26;
            }
            else
            {
                cyphered = 'a' + (uncyphered[i] + k - 'a')%26;
            }
            printf("%c", cyphered);
        }
        else
        {
            printf("%c", uncyphered[i]);
        }
    }
    printf("\n");
}
int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Invalid number of arguments!\n");
        return 1;
    }
    else{
        // next line imports argv[1] as int
        int k = atoi(argv[1]);
        string uncyphered = GetString();
        encode(uncyphered, k);
        return 0;
    }
}
