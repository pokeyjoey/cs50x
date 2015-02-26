/**
 * jpg.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * JPG-related data types.
 */

#include <stdint.h>

/**
 * Common Data Types 
 *
 * The data types in this section are essentially aliases for C/C++ 
 * primitive data types.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;

/**
 * JPGBLOCK
 *
 * This structure describes a jpg.
 * - if is the start of a jpg, the first four bytes of the block will be the following:
 *      0xff 0xd8 0xff 0xe0 or
 *      0xff 0xd8 0xff 0xe1
 *
 */
typedef struct
{
    BYTE biFirstByte;
    BYTE biSecondByte;
    BYTE biThirdByte;
    BYTE biFourthByte;
    BYTE biBytes508[508];
} __attribute__((__packed__))
JPGBLOCK;
