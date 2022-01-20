#include "anneal.h"
#include "score.h"
#include <pthread.h>
#include "solve.h"

void main()
{
    //int sudoku[SUDOKU_SIZE][SUDOKU_SIZE] = {0};
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
    /*
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
    */
    int sudoku[9][9] = {
        {0, 0, 0, 0, 0, 0, 8, 2, 0},
        {0, 2, 0, 3, 7, 0, 0, 5, 0},
        {1, 0, 0, 8, 0, 4, 0, 7, 3},
        {0, 7, 6, 9, 0, 0, 2, 0, 4},
        {0, 0, 0, 7, 0, 2, 0, 0, 0},
        {2, 0, 8, 0, 0, 1, 7, 3, 0},
        {4, 1, 0, 6, 0, 5, 0, 0, 7},
        {0, 5, 0, 0, 3, 8, 0, 9, 0},
        {0, 8, 3, 0, 0, 0, 0, 0, 0}};

    int mask[9][9] = {0};
    populate_sudoku(sudoku, mask);
    printf("sus\n");
    print_sudoku(mask);

    init_score((int *)&score, sudoku);
    //printf("score 9 %d\n", score[9]);
    //printf("score 11 %d\n", score[11]);
    int cscore = total_score(score);
    printf("total score -> %d\n", cscore);
    print_sudoku(sudoku);
    float sigma = get_sigma(score, sudoku, mask);
    printf("Sigma: %f\n", sigma);

    int new_score;
    int attempts = 0;

    int temp_sudoku[SUDOKU_SIZE][SUDOKU_SIZE];
    memcpy(temp_sudoku, sudoku, sizeof(int) * SUDOKU_SIZE * SUDOKU_SIZE);
    int temp_score[SUDOKU_SIZE * 2];
    memcpy(temp_score, score, sizeof(int) * SUDOKU_SIZE * 2);
    int xa, ya, xb, yb;
    int control = 0;

    while (score != 0)
    {

        attempt_new(temp_score, score, temp_sudoku, sudoku, mask, &control, sigma, iterations, cscore, &new_score);
        //printf("new score %d\n", new_score);
        //printf("new score %d\n", new_score);

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
                //printf("xa %d ya %d xb %d yb %d\n", xa, ya, xb, yb);
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
