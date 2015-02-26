#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {

    float change;
    int change_in_cents;
    int change_in_quarters = 0;
    int change_in_dimes = 0;
    int change_in_nickels = 0;
    int change_in_pennies = 0;            
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    int number_of_coins = 0;
    int number_of_quarters = 0;
    int number_of_dimes = 0;
    int number_of_nickels = 0;
    int number_of_pennies = 0;
    
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
    if (change_in_cents/quarter > 0){
        number_of_quarters = change_in_cents/quarter;
        change_in_quarters = number_of_quarters * quarter;
        change_in_cents = change_in_cents - change_in_quarters;
        number_of_coins = number_of_coins + number_of_quarters;
    }
    
    // Can change be made with dimes?
    if (change_in_cents/dime > 0){
        number_of_dimes = change_in_cents/dime;
        change_in_dimes = number_of_dimes * dime;
        change_in_cents = change_in_cents - change_in_dimes;
        number_of_coins = number_of_coins + number_of_dimes;
    }
        
    // Can change be made with nickels?
    if (change_in_cents/nickel > 0){
        number_of_nickels = change_in_cents/nickel;
        change_in_nickels = number_of_nickels * nickel;
        change_in_cents = change_in_cents - change_in_nickels;
        number_of_coins = number_of_coins + number_of_nickels;
    }   
    
    // Can change be made with pennies?
    if (change_in_cents/penny > 0){
        number_of_pennies = change_in_cents/penny;
        change_in_pennies = number_of_pennies * penny;
        change_in_cents = change_in_cents - change_in_pennies;
        number_of_coins = number_of_coins + number_of_pennies;        
    }
    
    // Print out the number of coins
    printf("%i\n", number_of_coins);
    
}
