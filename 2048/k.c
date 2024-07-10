#include <stdlib.h>
#include <math.h>
#include "k.h"
#include <stdio.h>

bool add_random_tile(struct game *game)
{
    int row, col;
    int free_cell = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (game->board[i][j] == ' ')
            {
                free_cell++;
            }
        }
    }

    if (free_cell == 0)
        return false;

    // find random, but empty tile
    do
    {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if (rand() % 2 == 0)
    {
        game->board[row][col] = 'A';
        return true;
    }
    else
    {
        game->board[row][col] = 'B';
        return true;
    }

    return false;
}

bool is_game_won(const struct game game)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (game.board[i][j] == 'K')
            {
                return 1;
            }
        }
    }

    return 0;
}

bool is_move_possible(const struct game game)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (game.board[i][j] == ' ')
            {
                return 1;
            }

            if ((i < SIZE - 1 && game.board[i][j] == game.board[i + 1][j]) ||
                (i > 0 && game.board[i][j] == game.board[i - 1][j]) ||
                (j < SIZE - 1 && game.board[i][j] == game.board[i][j + 1]) ||
                (j > 0 && game.board[i][j] == game.board[i][j - 1]))
            {
                return 1;
            }
        }
    }

    return 0;
}

bool update(struct game *game, int dy, int dx)
{
    if (dy == dx || dx > 1 || dx < -1 || (dy + dx == 0) || dy > 1 || dy < -1)
    {
        return 0;
    }

    // right
    if (dx == 1)
    {
        printf("right\n");
        for (int i = 0; i < SIZE; i++)
        {
            int index = SIZE - 1;
            for (int j = SIZE - 1; j >= 0; j--)
            {

                if (game->board[i][j] != ' ')
                {
                    game->board[i][index] = game->board[i][j];
                    if (index != j)
                    {
                        game->board[i][j] = ' ';
                    }
                    index--;
                }
            }

            for (int j = SIZE - 1; j > 0; j--)
            {
                if (game->board[i][SIZE - 1] == ' ')
                {
                    break;
                }
                else if (game->board[i][j - 1] == game->board[i][j] && game->board[i][j] != ' ')
                {
                    game->score = game->score + pow(2, (int)game->board[i][j] - 63);
                    game->board[i][j]++;
                    game->board[i][j - 1] = ' ';
                }
            }

            index = SIZE - 1;
            for (int j = SIZE - 1; j >= 0; j--)
            {

                if (game->board[i][j] != ' ')
                {
                    game->board[i][index] = game->board[i][j];
                    if (index != j)
                    {
                        game->board[i][j] = ' ';
                    }
                    index--;
                }
            }
        }
        return 1;
    }

    // left
    if (dx == -1)
    {
        printf("left\n");
        for (int i = 0; i < SIZE; i++)
        {
            int index = 0;
            for (int j = 0; j <= SIZE - 1; j++)
            {
                if (game->board[i][j] != ' ')
                {
                    game->board[i][index] = game->board[i][j];
                    if (index != j)
                    {
                        game->board[i][j] = ' ';
                    }
                    index++;
                }
            }

            for (int j = 0; j < SIZE - 2; j++)
            {
                if (game->board[i][0] == ' ')
                {
                    break;
                }
                else if (game->board[i][j + 1] == game->board[i][j] && game->board[i][j] != ' ')
                {
                    game->score = game->score + pow(2, (int)game->board[i][j] - 63);
                    game->board[i][j]++;
                    game->board[i][j + 1] = ' ';
                }
            }

            index = 0;
            for (int j = 0; j <= SIZE - 1; j++)
            {
                if (game->board[i][j] != ' ')
                {
                    game->board[i][index] = game->board[i][j];
                    if (index != j)
                    {
                        game->board[i][j] = ' ';
                    }
                    index++;
                }
            }
        }
        return 1;
    }

    // up
    if (dy == -1)
    {
        printf("up\n");
        for (int j = 0; j < SIZE; j++)
        {
            int index = 0;
            for (int i = 0; i <= SIZE - 1; i++)
            {
                if (game->board[i][j] != ' ')
                {
                    game->board[index][j] = game->board[i][j];
                    if (index != i)
                    {
                        game->board[i][j] = ' ';
                    }
                    index++;
                }
            }

            for (int i = 0; i < SIZE - 2; i++)
            {
                if (game->board[0][j] == ' ')
                {
                    break;
                }
                else if (game->board[i + 1][j] == game->board[i][j] && game->board[i][j] != ' ')
                {
                    game->score = game->score + pow(2, (int)game->board[i][j] - 63);
                    game->board[i][j]++;
                    game->board[i + 1][j] = ' ';
                }
            }

            index = 0;
            for (int i = 0; i <= SIZE - 1; i++)
            {
                if (game->board[i][j] != ' ')
                {
                    game->board[index][j] = game->board[i][j];
                    if (index != i)
                    {
                        game->board[i][j] = ' ';
                    }
                    index++;
                }
            }
        }
        return 1;
    }

    // down
    if (dy == 1)
    {
        printf("down\n");
        for (int j = 0; j < SIZE; j++)
        {
            int index = SIZE - 1;
            for (int i = SIZE - 1; i >= 0; i--)
            {
                if (game->board[i][j] != ' ')
                {
                    game->board[index][j] = game->board[i][j];
                    if (index != i)
                    {
                        game->board[i][j] = ' ';
                    }
                    index--;
                }
            }

            for (int i = SIZE - 1; i > 0; i--)
            {
                if (game->board[SIZE - 1][j] == ' ')
                {
                    break;
                }
                else if (game->board[i - 1][j] == game->board[i][j] && game->board[i][j] != ' ')
                {
                    game->score = game->score + pow(2, (int)game->board[i][j] - 63);
                    game->board[i][j]++;
                    game->board[i - 1][j] = ' ';
                }
            }

            index = SIZE - 1;
            for (int i = SIZE - 1; i >= 0; i--)
            {
                if (game->board[i][j] != ' ')
                {
                    game->board[index][j] = game->board[i][j];
                    if (index != i)
                    {
                        game->board[i][j] = ' ';
                    }
                    index--;
                }
            }
        }
        return 1;
    }

    return 0;
}
