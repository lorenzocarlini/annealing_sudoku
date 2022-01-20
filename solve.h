//#include <string.h>
void attempt_new(int *my_score[SUDOKU_SIZE * 2], int *score[SUDOKU_SIZE * 2], int *my_sudoku[SUDOKU_SIZE][SUDOKU_SIZE], int *sudoku[SUDOKU_SIZE][SUDOKU_SIZE], int *mask[SUDOKU_SIZE][SUDOKU_SIZE], int *control, float sigma, int iterations, int cscore, int *new_score)
{
    int xa, ya, xb, yb;
    for (int counter = 0; counter < iterations; counter++)
    {
        //printf("> %d\n", counter);
        //printf("---\n");

        random_positions(&xa, &ya, &xb, &yb, mask, my_score);
        //printf("??%d %d  -  %d %d\n", xa, ya, xb, yb);
        //print_sudoku(my_sudoku);
        //printf("%d %d %d %d \n", xa, ya, xb, yb);
        swap_sudoku(xa, ya, xb, yb, my_sudoku);
        //printf("a\n");
        //print_sudoku(my_sudoku);

        //print_sudoku(my_sudoku);
        update_score(my_score, my_sudoku, xa, ya, xb, yb);
        *new_score = total_score(my_score);
        //printf("rt> %d\n", *new_score);

        double rho = (exp(-(*new_score - cscore) / sigma));
        int ext = (double)(rand() % 3);
        if (ext == 2)
        {
            ext--;
        }
        sigma *= COOLING_RATE;

        if (!(ext < rho))
        {
            memcpy(my_sudoku, sudoku, sizeof(int) * SUDOKU_SIZE * SUDOKU_SIZE);
            memcpy(my_score, score, sizeof(int) * SUDOKU_SIZE * 2);
        }
        else
        {

            //printf("tempscore -> %d, sigma -> %f\n", new_score, sigma);
        }
    }
}
