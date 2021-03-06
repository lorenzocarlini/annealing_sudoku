#include "anneal.h"
#include "score.h"

void main()
{
    int sudoku[SUDOKU_SIZE][SUDOKU_SIZE] = {0};
    int score[SUDOKU_SIZE * 2] = {0};
    int iterations = SUDOKU_SIZE * SUDOKU_SIZE;
    srand(time(NULL));
    /*
    for (int x = 0; x < SUDOKU_SIZE; x++)
    {
        for (int y = 0; y < SUDOKU_SIZE; y++)
        {
            if (rand() % 9 == 0)
            {
                iterations--;
                sudoku[x][y] = rand() % 9 + 1;
            }
        }
    }
    */
    sudoku[0][0] = 4;
    sudoku[0][2] = 1;
    sudoku[4][1] = 2;
    sudoku[5][3] = 3;
    sudoku[4][7] = 5;
    sudoku[4][4] = 6;
    sudoku[5][8] = 7;
    sudoku[2][5] = 8;
    sudoku[5][2] = 9;
    sudoku[8][8] = 4;
    sudoku[7][5] = 1;

    populate_sudoku(sudoku);

    init_score((int *)&score, sudoku);
    //printf("score 9 %d\n", score[9]);
    //printf("score 11 %d\n", score[11]);
    int cscore = total_score(score);
    printf("total score -> %d\n", cscore);
    print_sudoku(sudoku);
    float sigma = get_sigma(score, sudoku);
    printf("Sigma: %f\n", sigma);

    int new_score;
    int attempts = 0;

    int temp_sudoku[SUDOKU_SIZE][SUDOKU_SIZE];
    memcpy(temp_sudoku, sudoku, sizeof(int) * SUDOKU_SIZE * SUDOKU_SIZE);
    int temp_score[SUDOKU_SIZE * 2];
    memcpy(temp_score, score, sizeof(int) * SUDOKU_SIZE * 2);
    int xa, ya, xb, yb;

    int backup_sudoku[SUDOKU_SIZE][SUDOKU_SIZE];
    memcpy(backup_sudoku, sudoku, sizeof(int) * SUDOKU_SIZE * SUDOKU_SIZE);
    int backup_score[SUDOKU_SIZE * 2];
    memcpy(backup_score, score, sizeof(int) * SUDOKU_SIZE * 2);

    while (score != 0)
    {
        for (int counter = 0; counter < iterations; counter++)
        {
            random_positions(&xa, &ya, &xb, &yb);
            //printf("??%d %d  -  %d %d\n", xa, ya, xb, yb);
            swap_sudoku(xa, ya, xb, yb, temp_sudoku);
            update_score((int *)&temp_score, temp_sudoku, xa, ya, xb, yb);
            new_score = total_score(temp_score);

            double rho = (exp(-(new_score - cscore) / sigma));
            int ext = (double)(rand() % 3);
            if (ext == 2)
            {
                ext--;
            }
            sigma *= COOLING_RATE;

            if (!(ext < rho))
            {
                memcpy(temp_sudoku, sudoku, sizeof(int) * SUDOKU_SIZE * SUDOKU_SIZE);
                memcpy(temp_score, score, sizeof(int) * SUDOKU_SIZE * 2);
            }
            else
            {

                //printf("tempscore -> %d, sigma -> %f\n", new_score, sigma);
            }
        }

        if (cscore <= 0)
        {
            printf("Amogus\n");
            printf("Score -> %d \n", cscore);
            print_sudoku(sudoku);
            break;
        }
        else
        {
            if (new_score < cscore)
            {
                cscore = new_score;
                memcpy(sudoku, temp_sudoku, sizeof(int) * SUDOKU_SIZE * SUDOKU_SIZE);
                memcpy(score, temp_score, sizeof(int) * SUDOKU_SIZE * 2);
                printf("Score -> %d \n", cscore);
                print_sudoku(sudoku);
                for (int tt = 0; tt < 18; tt++)
                {
                    printf("[%d]", score[tt]);
                }
                printf("\n");
            }

            else
            {
                //printf("fail.. %d\n", new_score);
                //print_sudoku(temp_sudoku);
                memcpy(temp_sudoku, sudoku, sizeof(int) * SUDOKU_SIZE * SUDOKU_SIZE);
                memcpy(temp_score, score, sizeof(int) * SUDOKU_SIZE * 2);
                attempts++;
            }
        }

        if (attempts > SUDOKU_SIZE * SUDOKU_SIZE)
        {
            //printf("sus\n");
            //printf("score -> %d, sigma -> %f\n", cscore, sigma);
            sigma += 2.0;
        }
    }
}

//compile -> gcc *.c -lm -o Output
