#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DIM_MIN 3
#define DIM_MAX 9

int board[DIM_MAX][DIM_MAX];

int d;

int tile_i;
int tile_j;
int blank_i;
int blank_j;

void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

void search(int tile);
bool legalmove(void);
void swaptile(int tile);

int main(int argc, string argv[])
{
    
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    
    greet();

    
    init();

    
    while (true)
    {
    
        clear();

    
        draw();

    
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

    
        if (won())
        {
            printf("ftw!\n");
            break;
        }

    
        printf("Tile to move: ");
        int tile = GetInt();
        
    
        if (tile == 0)
        {
            break;
        }

    
        fprintf(file, "%i\n", tile);
        fflush(file);

    
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

    
        usleep(500000);
    }
    
    
    fclose(file);

    
    return 0;
}


void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}


void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

void init(void)
{
    
    int n = (d*d) - 1;
    
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = n;
            n--;
        }
        printf("\n");
    }
    
    
    if (((d*d) - 1) % 2 != 0)
    {
        int temp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;
    }
    
    
    blank_i = d-1;
    blank_j = d-1;
}


void draw(void)
{
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] < 10) 
            {
                if (board[i][j] == 0) 
                {
                    printf(" [_] ");
                }
                else
                {
                printf(" [%d] ", board[i][j]);
                }
            }
            else
            {
                printf("[%d] ", board[i][j]);
            }
        }
        printf("\n"); //space between each line
    }
}


bool move(int tile)
{   
    if (tile > (d*d)-1 || tile < 1)
        return false;
   search(tile);
   if (legalmove())
    {
        swaptile(tile);
        return true;
    }
    else
        return false;
    
    return false;
}


bool won(void)
{

    int counter = 1;
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == counter)
                counter++;
        } 
    }
    
    if (counter == d*d && board[d-1][d-1] == 0)
        return true;
    else
        return false;
}


void search(int tile)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                tile_i = i;
                tile_j = j;
            } 
        }
    }
}


bool legalmove(void)
{
    
    if (tile_i > 0 && board[tile_i - 1][tile_j] == 0)
        return true;
    
    if (tile_i < d-1 && board[tile_i + 1][tile_j] == 0)
        return true;

    if (tile_j > 0 && board[tile_i][tile_j - 1] == 0)
        return true;

    if (tile_j < d-1 && board[tile_i][tile_j + 1] == 0)
        return true;
    else
        return false;
}


void swaptile(tile)
{
    int temp = board[tile_i][tile_j];
    board[tile_i][tile_j] = board[blank_i][blank_j];
    board[blank_i][blank_j] = temp;
    
    
    blank_i = tile_i;
    blank_j = tile_j;
}