#define SUDOKU_SIZE 9
#define ANNEAL_TEMP_SAMPLE 10

void populate_sudoku(int psudoku[SUDOKU_SIZE][SUDOKU_SIZE], int maskp[SUDOKU_SIZE][SUDOKU_SIZE])
{
    int available_numbers[SUDOKU_SIZE][SUDOKU_SIZE] = {1};
    for (int i = 0; i < SUDOKU_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_SIZE; j++)
        {
            available_numbers[i][j] = 1;
            maskp[i][j] = 0;
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
                maskp[i][j] = 1;
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

void random_positions(int *xa, int *ya, int *xb, int *yb, int mask[SUDOKU_SIZE][SUDOKU_SIZE], int score[SUDOKU_SIZE * 2])
{
    int notgood = 1;
    while (notgood == 1)
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
        if (!(mask[*xa][*ya] == 1 || mask[*xb][*yb] == 1))
        {
            notgood = 0;
        }
    }
}

/*
void random_positions(int *xa, int *ya, int *xb, int *yb, int mask[SUDOKU_SIZE][SUDOKU_SIZE], int score[SUDOKU_SIZE * 2])
{
    int score_quadx[3] = {0};
    int score_quady[3] = {0};
    int count_quad = 0;
    int suitable_quad = 0;
    int quad_x, quad_y = 0;
    for (int i = 0; i < SUDOKU_SIZE / 3; i++)
    {
        if (score[i * 3] + score[i * 3 + 1] + score[i * 3 + 2] > 0)
        {
            score_quadx[i] = 1;
            count_quad++;
        }
        if (score[i * 3 + 9] + score[i * 3 + 1 + 9] + score[i * 3 + 2 + 9] > 0)
        {
            score_quady[i] = 1;
            count_quad++;
        }
    }

    int notgood = 1;
    while (notgood == 1)
    {

        while (suitable_quad == 0)
        {
            quad_x = (rand() % SUDOKU_SIZE) % 3;
            quad_y = (rand() % SUDOKU_SIZE) / 3;
            if ((score_quadx[quad_x] == 1 || score_quady[quad_y] == 1))
            {
                suitable_quad = 1;
            }
        }

        //printf("quadx quady %d %d\n", quad_x, quad_y);
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
        if (!(mask[*xa][*ya] == 1 || mask[*xb][*yb] == 1))
        {
            notgood = 0;
        }
    }
}
*/
/*
void random_positions(int *xa, int *ya, int *xb, int *yb, int mask[SUDOKU_SIZE][SUDOKU_SIZE], int score[SUDOKU_SIZE * 2])
{
    int notgoodcoord = 1;
    int notgoodquad = 1;
    int quad_x, quad_y;
    int attempt = 0;
    int score_quadx[3] = {0};
    int score_quady[3] = {0};
    int count_quad = 0;
    //printf("scored", score[0]);

    for (int i = 0; i < SUDOKU_SIZE / 3; i++)
    {
        if (score[i * 3] + score[i * 3 + 1] + score[i * 3 + 2] > 0)
        {
            score_quadx[i] == 1;
            count_quad++;
        }
        if (score[i * 3 + 9] + score[i * 3 + 1 + 9] + score[i * 3 + 2 + 9] > 0)
        {
            score_quady[i] == 1;
            count_quad++;
        }
    }

    for (int i = 0; i < SUDOKU_SIZE / 3; i++)
    {
        for (int j = 0; j < SUDOKU_SIZE / 3; j++)
        {
            if (score_quadx[i] == 1 && score_quady[j] == 1)
            {
                quad_x = i;
                quad_y = j;
            }
        }
    }

    quad_x = (rand() % SUDOKU_SIZE) % 3;
    quad_y = (rand() % SUDOKU_SIZE) / 3;
    if ((score[quad_x] + score[quad_x + 1] + score[quad_x + 2] > 0) || (score[quad_y] + 9 + score[quad_y + 9 + 1] + score[quad_y + 9 + 2] > 0))
    {
        notgoodquad = 0;
    }

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
    //printf("xa %d xb %d ya %d yb %d", *xa, *ya, *xb, *yb);

    //printf("xa:%d,ya%d | xb%d,yb%d\n -- distance x:%d, distance y:%d\n", *xa, *ya, *xb, *yb, *xa - *xb, *ya - *yb);

    if (!(mask[*xa][*ya] == 1 || mask[*xb][*yb] == 1) || attempt > SUDOKU_SIZE * SUDOKU_SIZE)
    {
        notgoodcoord = 0;
    }

    //printf(">>[%d][%d] - [%d][%d]\n", *xa, *ya, *xb, *yb);
}
*/