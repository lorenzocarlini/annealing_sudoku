#include "anneal.h"
#include "score.h"

void main()
{
    int sudoku[SUDOKU_SIZE][SUDOKU_SIZE] = {0};
    int score[SUDOKU_SIZE * 2] = {0};
    srand(time(NULL));
    for (int x = 0; x < SUDOKU_SIZE; x++)
    {
        for (int y = 0; y < SUDOKU_SIZE; y++)
        {
            if (rand() % 9 == 0)
            {
                sudoku[x][y] = rand() % 9 + 1;
            }
        }
    }

    populate_sudoku(sudoku);

    init_score((int *)&score, sudoku);
    //printf("score 9 %d\n", score[9]);
    //printf("score 11 %d\n", score[11]);
    printf("total score -> %d\n", total_score(score));
    print_sudoku(sudoku);
    float sigma = get_sigma(score, sudoku);
    printf("Sigma: %f\n", sigma);
}

//compile -> gcc *.c -lm -o Output
