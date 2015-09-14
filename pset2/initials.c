#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

void initializeName(char name[])
{
    // only run if string exists
    int strlength = strlen(name);
    if(strlength > 0)
    {
        // the first LETTER will be an initial
        if(isalpha(name[0]))
        {
            printf("%c", toupper(name[0]));
        }
        // every letter that follows a non-letter is 
        // initialized 
        for(int j=1; j<strlength;j++)
            {
                if(isalpha(name[j]) && !isalpha(name[j-1]))
                {
                    printf("%c", toupper(name[j]));
                }
            }
        printf("\n");
    }
}

int main(void)
{
    //printf("Enter name: ");
    string name = GetString();
    initializeName(name);
}
