#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float owed;
    do
    {
        printf("How much do I owe you? ");
        owed = GetFloat();
    }
    while(owed < 0);
    
    int change = (int)((owed*100) + 0.5); 
    
    // printf("%.50f\n", owed);
    // printf("%d\n", change);
    
    int numCoins = 0;
    
    // Quarters
    
    numCoins += change / 25;
    change = change - (change / 25) * 25;
    
    // Dimes
    
    numCoins += change / 10;
    change = change - (change / 10) * 10;
    
    // Nickels
    
    numCoins += change / 5;
    change = change - (change / 5) * 5;
    
    //Pennies
    
    numCoins += change;
    
    printf("%d\n", numCoins);
}
