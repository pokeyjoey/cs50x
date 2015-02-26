#include <stdio.h>
#include <cs50.h>

int main (void) {

    printf("State your name: ");
    string name  = GetString();

    printf("hello, %s !\n", name);
    printf("goodbye!\n");

}

