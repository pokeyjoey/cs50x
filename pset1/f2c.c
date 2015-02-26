#include <stdio.h>
#include <cs50.h>

int main (void) {
    printf("Give me a temp in F: ");
    float f = GetFloat();
    
    float c = 5.0/9.0 * (f - 32.0);

    printf("%.1f\n",c);
}
