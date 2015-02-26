/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t  BYTE;

typedef struct
{
    BYTE biFirstByte;
    BYTE biSecondByte;
    BYTE biThirdByte;
    BYTE biFourthByte;
    BYTE biBytes508[508];
} __attribute__((__packed__))
JPGBLOCK;

// prototypes
bool is_start_of_jpg(JPGBLOCK* block_pointer);

int main(int argc, char* argv[])
{
    int file_number = 0;
    char title[8];
    bool start_writing = false;
    FILE* img;

    // open card file
    FILE* inptr = fopen("card.raw", "r");

    // struct to hold the buffer of data
    JPGBLOCK block;

    // open the first new img file
    sprintf(title, "%03d.jpg", file_number);
    img = fopen(title, "a");

    // repeat until end of card
    while (fread(&block, sizeof(JPGBLOCK), 1, inptr) == 1)
    {
        // is this the start of a new jpg ?
        if (is_start_of_jpg(&block))
        {
            // if start_writing is true, we already have an open file.
            // - close the current file before opening the next
            // - open the next file
            if (start_writing)
            {
                fclose(img);
                sprintf(title, "%03d.jpg", file_number);
                img = fopen(title, "a");
            }

            start_writing = true;

            file_number++;
        }

        // write a block to an img file
        if (start_writing)
        {
            fwrite(&block, sizeof(JPGBLOCK), 1, img);
        }
    }

    // close any remaining files
    fclose(img);
    fclose(inptr);
}

/**
 * Is this the start of a jpg?
 * - if is the start of a jpg, the first four bytes of the block will be the following:
 *      0xff 0xd8 0xff 0xe0 or
 *      0xff 0xd8 0xff 0xe1
 */
bool is_start_of_jpg(JPGBLOCK* block_pointer)
{
    if (block_pointer->biFirstByte == 0xff && block_pointer->biSecondByte == 0xd8 &&
        block_pointer->biThirdByte == 0xff && 
       (block_pointer->biFourthByte == 0xe0 || block_pointer->biFourthByte == 0xe1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

