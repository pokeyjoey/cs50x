#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void apply_caesar_cipher(string keyword, string message);
int get_index_of_letter_in_alphabet(char letter);
int get_converted_ascii_decimal_value(int key, char letter);
int get_ascii_of_ciphered_letter_in_alphabet(int key, char letter, int ascii_alphabet_start);

int capital_ascii_alphabet_start = 'A';
int lower_ascii_alphabet_start = 'a';

int main(int argc, string argv[])
{
    string keyword;
    string message;
 
    // Verify that we are receiving one command line argument
    // - if otherwise warn the user and return a 1
    if (argc == 2) {
        keyword = argv[1];
    } else {
        printf("You must supply a keyword!\n");
        return 1;
    }
    
    // Verify keyword is all alpha.
    // if keyword is not all alpha return 1
    for (int i=0, n = strlen(keyword); i < n; i++) {
        if (!isalpha(keyword[i])){
            printf("You must supply an alpha keyword!\n");
            return 1;
        }
    }
 
    // get a string of plaintext.
    // - if string is not all alpha return 1.
    do 
    {
        message = GetString();
    }
    while (strlen(message) < 1);
 
    // Encrypt the message using the Caesar Cipher.
    apply_caesar_cipher(keyword, message);
    
}

void apply_caesar_cipher(string keyword, string message){
    int key, ascii_character;
    int length_of_keyword = strlen(keyword);
    char letter;
    
     // Loop through the string and convert
    for (int i = 0, j = 0, n = strlen(message); i < n; i++)
    {
            // only convert letters
            if (isalpha(message[i])){
                // get key based on position in alphabet of jth letter in key word
                // - get current letter
                letter = keyword[j % length_of_keyword];
                key = get_index_of_letter_in_alphabet(letter);
                j++;
                
                // calculate Caesar Cipher
                ascii_character = get_converted_ascii_decimal_value(key, message[i]);
                printf("%c", ascii_character);
            } else {
                printf("%c", message[i]);
            }
     }
          
     printf("\n");
}

int get_index_of_letter_in_alphabet(char letter){
    int index_of_letter;
    
    // Subtract the ascii value of 'A' or 'a' from the letter.
    // The result is its index value in the array of letters 
    // where A/a = 0 and Z/z = 25.

    if (isupper(letter)){
        index_of_letter = (int) letter - capital_ascii_alphabet_start;
    } else {
        index_of_letter = (int) letter - lower_ascii_alphabet_start;
    }
    
    return index_of_letter;
}

int get_converted_ascii_decimal_value(int key, char letter){
    int converted_letter_ascii_decimal_value;
   
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
       
    // Subtract the ascii value of 'A' or 'a' from the letter.
    // The result is its index value in the array of letters 
    // where A/a = 0 and Z/z = 25.
    p = (int) letter - ascii_alphabet_start;
    
    // Add the key and divide by 26.
    // - c is the index value of the converted letter
    c = (p + key) % 26;
    
    // Add c to the ascii decimal value for 'A' to get
    // converted letter.
    index_of_letter = ascii_alphabet_start + c;

    return index_of_letter;
}
