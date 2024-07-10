#include "k.h"
#include "hof.h"
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <math.h>
#include <string.h>
#include <ncurses.h>

struct game game = {
    .board = {
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}},

    .score = 0};

struct player list[10];

struct player player = {
    .name = " ",
    .score = 0};

int get_color_for_letter(char letter)
{
    switch (letter)
    {
    case 'A':
        return 1;
    case 'B':
        return 2;
    case 'C':
        return 3;
    case 'D':
        return 4;
    case 'E':
        return 5;
    case 'F':
        return 6;
    default:
        return 7;
    }
}

void draw_board(struct game *game)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int color = get_color_for_letter(game->board[i][j]);
            attron(COLOR_PAIR(color));
            mvprintw(i * 2 + 3, j * 6 + 2, "%c ", game->board[i][j]);
            attroff(COLOR_PAIR(color));
            if (j < SIZE - 1)
                printw("|");
        }
        if (i < SIZE - 1)
        {
            mvprintw(i * 2 + 4, 0, "----------------------");
        }
    }
}

int main()
{
    int ch;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);

    add_random_tile(&game);
    add_random_tile(&game);
    int size = load(list);
    printf("Your name: ");
    scanf("%29s", player.name);

    bool game_over = false;

    while (1)
    {
        clear();
        mvprintw(0, 0, "%c", ch);
        mvprintw(1, 0, "Score: %d", game.score);

        draw_board(&game);

        if (game_over)
        {
            if (is_game_won(game))
            {
                mvprintw(SIZE * 2 + 3, 0, "You won!");
            }
            else if (!is_move_possible(game))
            {
                mvprintw(SIZE * 2 + 3, 0, "You cant move(((");
            }

            mvprintw(SIZE * 2 + 4, 0, "  ____                                              _ ");
            mvprintw(SIZE * 2 + 5, 0, " / ___| __ _ _ __ ___   ___    _____   _____ _ __  | |");
            mvprintw(SIZE * 2 + 6, 0, "| |  _ / _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__| | |");
            mvprintw(SIZE * 2 + 7, 0, "| |_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |    |_|");
            mvprintw(SIZE * 2 + 8, 0, " \\____|\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|    (_)");

            mvprintw(SIZE * 2 + 12, 0, "/////////LEADERBOARD/////////");
            int i;
            for (i = 0; i < size; i++)
            {
                mvprintw(SIZE * 2 + 13 + i, 0, " %s - %d", list[i].name, list[i].score);
            }

            mvprintw(SIZE * 2 + 14 + i, 0, "Press SPACE to exit.");
            refresh();
            while (getch() != ' ')
            {
            }
            break;
        }

        if (is_game_won(game))
        {
            game_over = true;
            continue;
        }
        else if (!is_move_possible(game))
        {
            game_over = true;
            continue;
        }
        else
        {
            mvprintw(SIZE * 2 + 4, 0, "Use WASD to move, SPACE to quit");
        }

        refresh();

        ch = getch();

        int dy = 0, dx = 0;
        switch (ch)
        {
        case 'w':
            dy = -1;
            break;
        case 's':
            dy = 1;
            break;
        case 'a':
            dx = -1;
            break;
        case 'd':
            dx = 1;
            break;
        case ' ':
            game_over = true;
            continue;
        }

        if (!game_over && (dy != 0 || dx != 0))
        {
            if (update(&game, dy, dx))
            {
                if (!add_random_tile(&game))
                {

                    game_over = true;
                }
            }
        }
    }

    player.score = game.score;
    bool result = add_player(list, &size, player);
    if (result)
        save(list, size);

    endwin();

    return 0;
}