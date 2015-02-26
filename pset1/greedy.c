#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {

    float change;
    int change_in_cents;           
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    int number_of_coins = 0;
    
    // Get the amount of change owed
    do {
        // Display a prompt for the user to input the amount of change owed.
        printf("O hai!  How much change is owed?\n");
    
        // Store the change 
        change = GetFloat();
    } 
    while (change  < 0) ;

    // convert the change to cents
    change_in_cents = round(change*100);
        
    // Can change be made with quarters?
    while (change_in_cents >= quarter) {
        number_of_coins = number_of_coins + 1;
        change_in_cents = change_in_cents - quarter;
    }
    
    // Can change be made with dimes?
    while (change_in_cents >= dime) {
        number_of_coins = number_of_coins + 1;
        change_in_cents = change_in_cents - dime;
    }
           
    // Can change be made with nickels?
    while (change_in_cents >= nickel) {
        number_of_coins = number_of_coins + 1;
        change_in_cents = change_in_cents - nickel;
    } 
    
    // Can change be made with pennies?
    while (change_in_cents >= penny) {
        number_of_coins = number_of_coins + 1;
        change_in_cents = change_in_cents - penny;
    } 
       
    // Print out the number of coins
    printf("%i\n", number_of_coins);
    
}
