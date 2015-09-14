/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

// helper function to search
bool binarySearch(int value, int values[], int left, int right)
{
    // terminate if max is less than min
    // if midpoint is less than zero or more than max
    
    int midpoint;
    if(right < left)
    {
        return false;
    }
    else
    {   
        // functionally the same as midpoint = (left + right)/2
        // but avoids integer overflow *consult notebook*
        
        midpoint = left + (right - left)/2;
        
        // if midpoint is equal to value, return true
        if(values[midpoint] == value)
        {
            printf("Found %d\n", values[midpoint]);
            return true;
        }
        
        // if midpoint is less than value, search right half 
        // make sure you return a recursive function!
        else if(values[midpoint] < value)
        {
            printf("Larger than %d, searching right half\n", values[midpoint]);
            return binarySearch(value, values, midpoint+1, right);
        }
        
        // if midpoint is greater than value, search left half
        else if(values[midpoint] > value)
        {
            printf("Smaller than %d, searching left half\n", values[midpoint]);
            return binarySearch(value, values, left, midpoint-1);
        }
    }
    return false;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    /** linear searching algorithm
    *for(int i = 0; i < n; i++)
    *{
    *    if(values[i] == value)
    *    {
    *        return true;
    *    }
    *}
    *return false;
    */
    
    // binary searching algorithm 
    return binarySearch(value, values, 0, n-1);
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // insertion sort
    // arrays are passed by reference - changes are done onto array
    // integers, otherwise, are copies when sent to another function
    for(int i = 0; i < n; i++)
    {
        for( int j = i; j > 0 && values[j-1] > values[j]; j--)
        {
            int smallerValue = values[j];
            values[j] = values[j-1];
            values[j-1] = smallerValue;
        }
    }
    return;
}
