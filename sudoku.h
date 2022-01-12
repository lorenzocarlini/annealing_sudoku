#define SUDOKU_SIZE 9
#define ANNEAL_TEMP_SAMPLE 10

void populate_sudoku(int psudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
    int available_numbers[SUDOKU_SIZE][SUDOKU_SIZE] = {1};
    for (int i = 0; i < SUDOKU_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_SIZE; j++)
        {
            available_numbers[i][j] = 1;
        }
    }

    for (int i = 0; i < SUDOKU_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_SIZE; j++)
        {
            if (psudoku
                    [i][j] != 0)
            {
                //printf("quad %d \n", (j / 3 + (i / 3) * 3));
                available_numbers[j / 3 + (i / 3) * 3][psudoku[i][j] - 1] = 0;
            }
        }
    }
    for (int i = 0; i < SUDOKU_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_SIZE; j++)
        {
            if (psudoku
                    [i][j] == 0)
            {
                //printf("quad %d \n", (j / 3 + (i / 3) * 3));
                int found = 0;
                int counter = 0;
                while (counter < SUDOKU_SIZE && found == 0)
                {
                    if (available_numbers[j / 3 + (i / 3) * 3][counter] == 1)
                    {
                        found = counter + 1;
                        //printf("found %d\n", found);
                        available_numbers[j / 3 + (i / 3) * 3][counter] = 0;
                    }
                    counter++;
                }
                psudoku[i][j] = found;
                //printf("%d\n", psudoku[i][j]);
                //available_numbers[j / 3 + (i / 3) * 3][psudoku[i][j]] = 1;
            }
        }
    }
};

void print_sudoku(int psudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
    for (int i = 0; i < SUDOKU_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_SIZE; j++)
        {
            printf("%d", psudoku[i][j]);
            if (j == 2 || j == 5)
            {
                printf(" ");
            }
        }
        printf("\n");
        if (i == 2 || i == 5)
        {
            printf("\n");
        }
    }
    printf("\n");
}

void swap_sudoku(int xa, int ya, int xb, int yb, int psudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
    int temp = psudoku[xa][ya];
    psudoku[xa][ya] = psudoku[xb][yb];
    psudoku[xb][yb] = temp;
    //printf("[%d,%d][%d,%d]\n", xa, ya, xb, yb);
}

void random_positions(int *xa, int *ya, int *xb, int *yb)
{

    int quad_x = (rand() % SUDOKU_SIZE) % 3;
    int quad_y = (rand() % SUDOKU_SIZE) / 3;
    //printf("quadx:%d quady:%d\n", quad_x, quad_y);
    *xa = rand() % (SUDOKU_SIZE / 3);
    *ya = rand() % (SUDOKU_SIZE / 3);
    *xb = rand() % (SUDOKU_SIZE / 3);
    *yb = rand() % (SUDOKU_SIZE / 3);
    //printf(">[%d][%d] - [%d][%d]\n", *xa, *ya, *xb, *yb);
    //printf("-xa:%d,xb%d,ya%d,yb%d\n", *xa, *xb, *ya, *yb);
    *xa += quad_x * 3;
    *xb += quad_x * 3;
    *ya += quad_y * 3;
    *yb += quad_y * 3;
    //printf("xa:%d,ya%d | xb%d,yb%d\n -- distance x:%d, distance y:%d\n", *xa, *ya, *xb, *yb, *xa - *xb, *ya - *yb);
    if (!(*xa - *xb > -3 && *xa - *xb < 3))
    {
        printf("sussy imposter\n");
    }
    if (!(*ya - *yb > -3 && *ya - *yb < 3))
    {
        printf("sussy imposter\n");
    }
    //printf(">>[%d][%d] - [%d][%d]\n", *xa, *ya, *xb, *yb);
}