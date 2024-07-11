#include <stdlib.h>
#include <math.h>
#include "k.h"
#include <stdio.h>

bool add_random_tile(struct game *game)
{
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
    {
        return false;
    }

    int target = rand() % free_cell;
    int current = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (game->board[i][j] == ' ')
            {
                if (current == target)
                {
                    game->board[i][j] = (rand() % 2 == 0) ? 'A' : 'B';
                    return true;
                }
                current++;
            }
        }
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
    bool changed = false;
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
                        changed = true;
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
                    game->board[i][j]++;
                    game->score += pow(2, game->board[i][j] - 'A' + 1);
                    for (int k = j - 1; k > 0; k--)
                    {
                        game->board[i][k] = game->board[i][k - 1];
                    }
                    game->board[i][0] = ' ';
                    changed = true;
                }
            }
        }
        return changed;
    }

    // left
    if (dx == -1)
    {
        printf("left\n");
        for (int i = 0; i < SIZE; i++)
        {
            int index = 0;
            for (int j = 0; j < SIZE; j++)
            {
                if (game->board[i][j] != ' ')
                {
                    game->board[i][index] = game->board[i][j];
                    if (index != j)
                    {
                        game->board[i][j] = ' ';
                        changed = true;
                    }
                    index++;
                }
            }

            for (int j = 0; j < SIZE - 1; j++)
            {
                if (game->board[i][0] == ' ')
                {
                    break;
                }
                else if (game->board[i][j + 1] == game->board[i][j] && game->board[i][j] != ' ')
                {
                    game->board[i][j]++;
                    game->score += pow(2, game->board[i][j] - 'A' + 1);

                    for (int k = j + 1; k < SIZE - 1; k++)
                    {
                        game->board[i][k] = game->board[i][k + 1];
                    }
                    game->board[i][SIZE - 1] = ' ';
                    changed = true;
                }
            }
        }
        return changed;
    }

    // up
    if (dy == -1)
    {
        printf("up\n");
        for (int j = 0; j < SIZE; j++)
        {
            int index = 0;
            for (int i = 0; i < SIZE; i++)
            {
                if (game->board[i][j] != ' ')
                {
                    game->board[index][j] = game->board[i][j];
                    if (index != i)
                    {
                        game->board[i][j] = ' ';
                        changed = true;
                    }
                    index++;
                }
            }

            for (int i = 0; i < SIZE - 1; i++)
            {
                if (game->board[0][j] == ' ')
                {
                    break;
                }
                else if (game->board[i + 1][j] == game->board[i][j] && game->board[i][j] != ' ')
                {
                    game->board[i][j]++;
                    game->score += pow(2, game->board[i][j] - 'A' + 1);
                    for (int k = i + 1; k < SIZE - 1; k++)
                    {
                        game->board[k][j] = game->board[k + 1][j];
                    }
                    game->board[SIZE - 1][j] = ' ';
                    changed = true;
                }
            }
        }
        return changed;
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
                        changed = true;
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
                    game->board[i][j]++;
                    game->score += pow(2, (int)game->board[i][j] - 'A' + 1);
                    for (int k = i - 1; k > 0; k--)
                    {
                        game->board[k][j] = game->board[k - 1][j];
                    }
                    game->board[0][j] = ' ';
                    changed = true;
                }
            }
        }
        return changed;
    }

    return changed;
}
