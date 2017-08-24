#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("Usage: resize scale infile outfile\n");
        return 1;
    }
    int scale = atoi(argv[1]);
    if(scale > 100 || scale < 1)
    {
        printf("Scale must be a positive int less than or equal to 100\n");
        return 1;
    }
    char* infile = argv[2];
    char* outfile = argv[3];
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    } 
    int originalWidth = bi.biWidth;
    int originalHeight = bi.biHeight;
    bi.biWidth *= scale;
    bi.biHeight *= scale;
    int originalPadding =  (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + padding);
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER); 
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));
    for (int i = 0, biHeight = abs(originalHeight); i < biHeight; i++)
    {
        int tracker = 0;
        for (int j = 0; j < originalWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for(int count = 0; count < scale; count++)
            {
                *(buffer+(tracker)) = triple;
                tracker++;
            }
        }
        fseek(inptr, originalPadding, SEEK_CUR);
           for(int r = 0; r < scale; r++)
           {
                fwrite((buffer), sizeof(RGBTRIPLE), bi.biWidth, outptr);

                for (int k = 0; k < padding; k++)
                    fputc(0x00, outptr);
           }        
    }
    free(buffer);
    fclose(inptr);
    fclose(outptr);
    return 0;
}
