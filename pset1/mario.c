#include <stdio.h>
#include <cs50.h>
 
int main(void)
{
    // variables
    int height = -1;
    int initial_pounds = 2;
    int spaces;
    int pounds;
    
    // Get the height of the pyramid
    do {
        // Display a prompt for the user to input the height of the pyramid.
        printf("Height: ");
    
        // Store the height 
        height = GetInt();
    } 
    while ((height < 1) || (height > 23)) ;
    
    // Set initial length of spaces and pounds to be displayed
    spaces = (height + 1) - initial_pounds;
    pounds = initial_pounds;
    
    // loop height times - number of rows in the pyramid
    for (int n = 0; n < height; ++n) {
    
        // print the correct number of spaces
        for (int x = 0; x < spaces; x++) {
            printf(" ");
        }
        
        // print the correct number of pounds
        for (int y = 0; y < pounds; y++) {
            printf("#");
        }

        // print the carriage return
        printf("\n");
        
        // Number of spaces for each row will decrease by one.
        // Number of pounds in each row will increase by one.        
        spaces--;
        pounds++;
    }
    
    return 0;
}
