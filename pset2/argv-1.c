#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{

    printf("argc: %i\n", argc);
    printf("argc < 2: %i\n", (argc < 2));
    if (argc < 2){
        printf("returning 1");
        //return 1;
    }
    
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
        printf("%i\n", argc);
    }
}

