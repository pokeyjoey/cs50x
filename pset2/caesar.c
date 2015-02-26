#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void apply_caesar_cipher(int key, string message);
int get_converted_ascii_decimal_value(int key, char letter);
int get_ascii_of_ciphered_letter_in_alphabet(int key, char letter, int ascii_alphabet_start);

int main(int argc, string argv[])
{
    int key;
    string message;
 
    // Verify that we are receiving one command line argument
    // - otherwise warn the user and return a 1
    if (argc == 2) {
        key = atoi(argv[1]);
    } else {
        printf("You must supply a non negative integer!\n");
        return 1;
    }
 
    // get a string of plaintext
    do 
    {
        message = GetString();
    }
    while (strlen(message) < 1);
 
    // Encrypt the message using the Caesar Cipher.
    apply_caesar_cipher(key, message);
    
}

void apply_caesar_cipher(int key, string message){
    int ascii_character;
        
     // Loop through the string and convert
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        // only convert letters
        if (isalpha(message[i])){
            ascii_character = get_converted_ascii_decimal_value(key, message[i]);
            printf("%c", ascii_character);
        } else {
            printf("%c", message[i]);
        }
     }
     
     printf("\n");
}

int get_converted_ascii_decimal_value(int key, char letter){
    int converted_letter_ascii_decimal_value;
    int capital_ascii_alphabet_start = 'A';
    int lower_ascii_alphabet_start = 'a';
    
    if (isupper(letter)){
        converted_letter_ascii_decimal_value = get_ascii_of_ciphered_letter_in_alphabet(
            key, letter, capital_ascii_alphabet_start);
    } else {
        converted_letter_ascii_decimal_value = get_ascii_of_ciphered_letter_in_alphabet(
            key, letter, lower_ascii_alphabet_start);
    }
    
    return converted_letter_ascii_decimal_value;
}

int get_ascii_of_ciphered_letter_in_alphabet(int key, char letter, int ascii_alphabet_start){
    int index_of_letter, p, c;
       
    // Subtract the ascii value of capital A from the letter.
    // The result is its index value in the array of captital letters 
    // where A = 0 and Z = 25.
    p = (int) letter - ascii_alphabet_start;
    
    // Add the key and divide by 26.
    // - c is the index value of the converted letter
    c = (p + key) % 26;
    
    // Add c to the ascii decimal value for 'A' to get
    // converted letter.
    index_of_letter = ascii_alphabet_start + c;

    return index_of_letter;
}
