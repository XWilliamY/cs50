#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // height starts at -1 to allow for while loop
    
    int height = -1;
    
    // reloops if not non-negative integer no more than 23
    
    while((height < 0) || (height > 23))
    {
        printf("Enter pyramind height: ");
        //scanf("%d", &height);
        height = GetInt();
    }
    
    // printf("%d\n", height);   
    
    if(height == 1)
    {
        printf("##\n");
    }
    else
    {
        int blocks = 2;
        int i = 0;
        while(i < height)
        {
        // print spaces
        int j = 0;
        while(j < (height- blocks + 1))
        {
            printf(" ");
            j++;
        }
        j = 0;
        
        // print blocks
        while(j < blocks)
        {
            printf("#");
            j++;
        }
        i++;
        blocks++;
        printf("\n");
        }
    }            
}

