/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // ensure proper usage
    int size_multiplier = atoi(argv[1]);
    if (size_multiplier < 1 || size_multiplier > 100)
    {
        printf("n, the resize factor, must satisfy 0 < n <= 100.\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf_infile, bf_outfile;
    fread(&bf_infile, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi_infile, bi_outfile;
    fread(&bi_infile, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_infile.bfType != 0x4d42 || bf_infile.bfOffBits != 54 || bi_infile.biSize != 40 || 
        bi_infile.biBitCount != 24 || bi_infile.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // set outfile headers to infile headers
    bf_outfile = bf_infile;
    bi_outfile = bi_infile;

    // modify the outfile headers for resizing in BITMAPINFOHEADER
    // - biSizeImage: total size of image in bytes
    //   + includes pixels and padding
    // - biWidth: width of image in pixels
    //   + does not include padding
    // - biHeight: heightof image in pixels
    bi_outfile.biWidth = bi_outfile.biWidth * size_multiplier;
    bi_outfile.biHeight = bi_outfile.biHeight * size_multiplier;

    // determine padding for scanlines for the infile
    int padding_infile = (4 - (bi_infile.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for scanlines for the outfile
    int padding_outfile = (4 - (bi_outfile.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine length of infile row
    int length_of_infile_row_bytes = (bi_infile.biWidth * 3) + padding_infile;

    // determine the biSizeImage for the outfile: each pixel is 3 bytes
    // - bytes in a row : width * 3 (bytes in a pixel)
    // - bytes in a row padding 
    int outfile_size_image_pixels = ((bi_outfile.biWidth * 3) * bi_outfile.biHeight);
    int outfile_size_padding_pixels = padding_outfile * bi_outfile.biHeight;
    int outfile_image_size = abs(outfile_size_image_pixels + outfile_size_padding_pixels);

    // cast to proper type
    bi_outfile.biSizeImage = (uint32_t) outfile_image_size;
    bf_outfile.bfSize = (uint32_t) (outfile_image_size + 54); 

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_outfile, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_outfile, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi_infile.biHeight); i < biHeight; i++)
    {
        // repeat horizontal resizing size_multiplier times
        for (int l = 0; l < size_multiplier; l++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi_infile.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int m = 0; m < size_multiplier; m++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any in infile
            fseek(inptr, padding_infile, SEEK_CUR);

            // add padding in outfile
            for (int k = 0; k < padding_outfile; k++)
            {
                fputc(0x00, outptr);
            }

            // if we havnt copied size_multiplier rows,
            // skip back to beginning of row in infile
            if (l < size_multiplier-1)
            {
                fseek(inptr, -length_of_infile_row_bytes, SEEK_CUR);
            }
        } 
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
