#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void encode (string uncyphered, string key)
{
    int index = 0;
    char cyphered;
    char keyword;
    for(int i = 0; i < strlen(uncyphered); i++)
    {
        if(isalpha(uncyphered[i]))
        {
            // if we exceed the length of the key
            if(index >= strlen(key))
            {
                index = 0;
            }
            
            // create keyword to encrypt the text
            if(isupper(key[index]))
            {
                keyword = key[index] - 'A';
            }
            else
            {
                keyword = key[index] - 'a';
            }
            
            // encrypt the text using similar algorithm for caesar's cipher
            if(isupper(uncyphered[i]))
            {    
                cyphered = 'A' + (uncyphered[i] + keyword - 'A')%26;
            }
            else
            {
                cyphered = 'a' + (uncyphered[i] + keyword - 'a')%26;
            }
            index ++;
            printf("%c", cyphered);
        }
        else
        {
            printf("%c", uncyphered[i]);
        }
    }
    printf("\n");    
}

int main(int argc, string argv [])
{
    if(argc != 2)
    {
        printf("Invalid number of command-line args!\n");
        return 1;
    }
    for(int i = 0; i < strlen(argv[1]); i++)
    {
        if(!isalpha(argv[1][i]))
        {
            printf("Non-alphabetical character detected!\n");
            return 1;
        }
    }
    string uncyphered = GetString();
    encode(uncyphered, argv[1]);
    return 0;
}
