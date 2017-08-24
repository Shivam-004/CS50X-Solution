#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: whodunnit cluefile \n");
        return 1;
    }
    FILE* clue_ptr = fopen(argv[1], "r");
    if (clue_ptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }
    FILE* solution_ptr = fopen("solution.bmp", "w");
    if (solution_ptr == NULL)
    {
        fclose(clue_ptr);
        fprintf(stderr, "Could not create %s.\n", "solution.bmp");
        return 3;
    }
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, clue_ptr);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, clue_ptr);
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(solution_ptr);
        fclose(clue_ptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, solution_ptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, solution_ptr);
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, clue_ptr);
            if(triple.rgbtRed == 255)
            {
				triple.rgbtRed = 0;
  				triple.rgbtBlue = 100;
				triple.rgbtGreen = 60;
            } 
            fwrite(&triple, sizeof(RGBTRIPLE), 1, solution_ptr);
        }
        fseek(clue_ptr, padding, SEEK_CUR);
        for (int k = 0; k < padding; k++)
            fputc(0x00, solution_ptr);
    }
    fclose(clue_ptr);
    fclose(solution_ptr);
    return 0;
}
