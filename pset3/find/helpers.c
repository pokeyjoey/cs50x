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

// uncomment the following line to debug any inconsistent results.
//#define DEBUG

/**
 * Prints out an array of ints.
 * - useful for debugging.
 */
void print_array(int print_array[], int min, int max)
{
    for (int i = min; i < max; i++)
    {
        printf("%i | ", print_array[i]);
    }
    printf("\n");
}


/**
 * Returns the midpoint between two numbers.
    - since this is integer division, this will work for even and odd numbers.
    - for an even number like 4, 4/2 is 2 which is the approximate mindpoint 
      in whole numbers.
    - for an odd number like 5, 5/2 = 2.5 a float. But since this is integer
      division, the fractional part is thrown away giving the exact midpoint.
    hints for this solution from Prgramming in C discussion in chapter 10 on 
    binary searches.
 */
int find_midpoint(int min, int max)
{
    int midpoint;

    midpoint = (min + max) / 2;

    return midpoint;
}

/**
 * Returns true if value is in array of n values, else returns false.
 *
 * inspiration for solution courtesy of Binary Search short by
 * Patrick Schmid.
 */
bool binary_search(int value, int values[], int min, int max)
{
    #ifdef DEBUG
        printf("binary_search\n");
        printf("min: %i | ", min);
        printf("max: %i\n", max);
        print_array(values, min, max);
    #endif

    int midpoint;

    if (max < min)
    {
        return false;
    }
    else
    {
        // find the midpoint of the array.
        // - min and max are the indices of the bounds of the
        //   array elements we are currently looking at.
        midpoint = find_midpoint(min, max);

        // determine where the key is located within the array
        // - if the value at the midpoint is less than the value we 
        //   are looking for, call binary_search with the bounds being
        //   above the midpoint.
        // - else if the value at the midpoint is greater than the value
        //   we are looking for, call binary_search with the bounds being
        //   below the midpoint.
        // - else we have found the value, return true.
        if (values[midpoint] < value)
        {
            return binary_search(value, values, midpoint + 1, max);
        }
        else if (values[midpoint] > value)
        {
            return binary_search(value, values, min, midpoint - 1);
        }
        else
        {
            return true;
        }
    }
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    bool in_array = false;

    // if n is not a positive integer return false.
    if (n < 0)
    {
        return false;
    }

    // search for value in the values array
    in_array = binary_search(value, values, 0,  n);

    return in_array;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Use a bubble sort to sort this array.
    bool swapped = false;
    int temp_values_i, temp_values_i_plus_1;

    #ifdef DEBUG
        print_array(values, 0, n);
    #endif

    do
    {
        swapped = false;

        for (int i = 0; i < n-1; i++)
        {
            // if the current element of the array is larger
            // than the next element:
            // - set the swapped boolean variable to true.
            if (values[i] > values[i+1])
            {
                // store the unsorted values in temperary variables
                temp_values_i = values[i];
                temp_values_i_plus_1 = values[i+1];

                // swap temp values in the array.
                values[i] = temp_values_i_plus_1;
                values[i+1] = temp_values_i;

                // set the swap boolean variable to true.
                swapped = true;
            }
        }
    
        #ifdef DEBUG
            print_array(values, 0, n);
        #endif
    } 
    while (swapped == true);

    return;
}
