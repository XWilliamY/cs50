/**
 * how to I/O files
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main (int argc, char* argv[])
{

    // ensure proper usage
    if(argc != 3)
    {
        printf("Usage: ./howIO infile outfile\n");
        return 1; // return non-zero for errors
    }
    
    // remember infile and outfile names
    char* infile = argv[1];
    char* outfile = argv[2];
    
    // read infile into inptr
    FILE* inptr = fopen(infile, "r");
    if(inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
    
    // read outfile into outptr
    FILE* outptr = fopen(outfile, "w");
    if(outptr == NULL)
    {
        printf("Could not create %s.\n", outfile);
        return 3;
    }
    
    // reading by scanline
    // fread(&data, size, number, inptr);
    // &data: pointer to a struct which will contain the bytes
    // size: size of each element to read: sizeof
    // number: number of elements
    // inptr: FILE*
    
    // read infile's BITMAPFILEHEADER into bf variable from inptr
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER into bi variable from inptr
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // write outfile's BITMAPFILEHEADER to bf of outptr
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER to bi of outptr
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    /**
     *bi.biWidth would give you the width of pixels
     *  let's say you have a width of 7
     *sizeof(RGBTRIPLE) gives you what the name implies 
     *  let's say you have 24 bits to a pixel 
     *
     *the idea is that if the equation above is not divisible by 4
     *that you then must add padding to each row 
     *so if you have 8 pixels per row, and you have 24 bits per pixel
     *24 bits/ 8 bits in a byte = 3 bytes per pixel
     *3 bytes per pixel * 8 pixels = 24! You're set. 
     */ 
     
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
    //note the abs(bi.biHeight)
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
   
    
