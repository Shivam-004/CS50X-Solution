#include <cs50.h>
#include <stdio.h>


int main(void) 
{
	
	int pyramid_height = 0;
	do {
		printf("Height:");
		pyramid_height = GetInt();
        if (pyramid_height == 0)
        {
            return 0;
        }
	} while (pyramid_height < 1 || pyramid_height > 23);

	for(int i = 0; i < pyramid_height; i++) 
	{
	    for(int j = 0; j < pyramid_height-i-1; j++)
        {
            printf(" ");
        }
        for(int k = 0; k < i+1; k++)
		{
			printf("#");
		}
		printf("  ");
		for(int l = 0; l < i+1; l++)
		{
			printf("#");
		}
		printf("\n");
	}	
	return 0;
}