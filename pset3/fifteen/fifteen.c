/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// uncomment to debug
//#define DEBUG

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;
int underscore = 95;
int underscore_row;
int underscore_col;
int tile_row;
int tile_col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
void find_tile(int tile);
void swap(int tile_row_location, int tile_col_location, int tile);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    int d_squared = d*d;

    #ifdef DEBUG
        printf("init\n");
        printf("d*d %i\n", d_squared);
    #endif

    int board_value = d_squared - 1;

    // initialize the board with numbers from d*d - 1 to 1
    // in descending order.
    for (int j = 0; j < d; j++)
    {
        for (int k = 0; k < d; k++)
        {
            #ifdef DEBUG
                printf("[%i]:[%i]\n", j , k);
                printf("board_value: %i\n", board_value);
            #endif

            board[j][k] = board_value;
            board_value--;
        }
    }

    // insert the ascii value of the underscore character
    // in the lower right hand corner of the d x d array.
    underscore_row = d-1;
    underscore_col = d-1;
    board[underscore_row][underscore_col] = underscore;

    // if the number of tiles is odd, swap the location of 1 and 2.
    if ((d_squared % 2) == 0)
    {
        board[d-1][d-3] = 1;
        board[d-1][d-2] = 2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    printf("\n");

    for (int j = 0; j < d; j++)
    {
        for (int k = 0; k < d; k++)
        {
            if (board[j][k] == underscore)
            {
                printf(" %c ", underscore);
            }
            else
            {
                printf("%2d ", board[j][k]);
            }
        }

        // start a new line for the board.
        printf("\n\n");
    }
}

/**
 * Find the postion of the tile to move.
 * Performing a linear search since the array is not sorted.
 */
void find_tile(int tile)
{
    #ifdef DEBUG
        printf("find_tile\n");
    #endif

    for (int j = 0; j < d; j++)
    {
        for (int k = 0; k < d; k++)
        {
            #ifdef DEBUG
                printf("[%i]:[%i] %i\n", j , k, board[j][k]);
            #endif

            if (board[j][k] == tile)
            {
                tile_row = j;
                tile_col = k;

                #ifdef DEBUG
                    printf("[%i]:[%i] %i\n", tile_row, tile_col, board[tile_row][tile_col]);
                #endif
            }
        }
    }
}

/**
 * Swap the location of the tile and underscore.
 */
void swap(int underscore_row_location, int underscore_col_location, int tile)
{
        // swap locations
        board[underscore_row_location][underscore_col_location] = tile;
        board[tile_row][tile_col] = underscore;

        // updated underscore location
        underscore_row = tile_row;
        underscore_col = tile_col;
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    bool tile_moved;

    // find the tile
    find_tile(tile);

    // Does the underscore border the tile location?
    if ((tile_row == underscore_row) && (tile_col-1 == underscore_col))
    {
        // underscore is left of the tile location
        swap(tile_row, tile_col-1, tile);
        tile_moved = true;
    }
    else if ((tile_row == underscore_row) && (tile_col+1 == underscore_col))
    {
        // underscore is right of the tile location
        swap(tile_row, tile_col+1, tile);
        tile_moved = true;
    }
    else if ((tile_row+1 == underscore_row) && (tile_col == underscore_col))
    {
        // underscore is above of the tile location
        swap(tile_row+1, tile_col, tile);
        tile_moved = true;
    }
    else if ((tile_row-1 == underscore_row) && (tile_col == underscore_col))
    {
        // underscore is below of the tile location
        swap(tile_row-1, tile_col, tile);
        tile_moved = true;
    }
    else
    {
        // tile is not in an adjacent space
        tile_moved = false;
    }

    return tile_moved;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int sorted_value = 1;

    // if the game is won, the board elements should
    // be alinged in ascending order.
    for (int j = 0; j < d; j++)
    {
        for (int k = 0; k < d; k++)
        {
            #ifdef DEBUG
                printf("[%i]:[%i]\n", j , k);
                printf("sorted_value: %i\n", sorted_value);
            #endif

            if (board[j][k] != sorted_value)
            {
                if (j == d-1 && k == d-1 && board[j][k] == underscore)
                {
                    return true;
                }
                else 
                {
                    return false;
                }
            }
            else
            {
                sorted_value++;
            }
        }
    }

    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
