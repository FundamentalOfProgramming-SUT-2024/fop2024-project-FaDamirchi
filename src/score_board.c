#include "score_board.h"
#include "global_defines.h"
#include "manage_users.h"

#define PLAYERS_PER_PAGE 6  // Tedad bazikon dar har safhe

// function to compare scores
int compare_scores(const void *a, const void *b)
{
    int scoreA, scoreB;
    sscanf(*(char **)a, "%*[^:]:%d", &scoreA);
    sscanf(*(char **)b, "%*[^:]:%d", &scoreB);
    return scoreB - scoreA;
}

void show_score_board(char *username)
{
    FILE *file = fopen(SCORES_FILE, "r");

    if (!file)
    {
        perror("Error opening scores file");
        return;
    }

    char *players[100];
    int count = 0;
    char buffer[512];

    // Read player data into an array
    while (fgets(buffer, sizeof(buffer), file) && count < 100)
    {
        players[count] = strdup(buffer);
        count++;
    }
    fclose(file);

    // Sort players by score
    qsort(players, count, sizeof(char *), compare_scores);

    curs_set(0);
    noecho();
    keypad(stdscr, TRUE); // Enable arrow key inputs

    int current_page = 0;
    int total_pages = (count + PLAYERS_PER_PAGE - 1) / PLAYERS_PER_PAGE; // Ceiling division

    int ch;
    while (1)
    {
        clear();

        int start_index = current_page * PLAYERS_PER_PAGE;
        int end_index = (start_index + PLAYERS_PER_PAGE > count) ? count : start_index + PLAYERS_PER_PAGE;

        mvprintw(2, 5, "(Page %d/%d)", current_page + 1, total_pages);

        for (int i = start_index; i < end_index; i++)
        {
            int y = 5 + (i - start_index) * 4;
            int x = 15;

            char player_username[320];
            int score, gold, experience, games_number;
            sscanf(players[i], "%319[^:]:%d-%d-%d-%d", player_username, &score, &gold, &experience, &games_number);

            bool is_current_user = (username != NULL && strcmp(player_username, username) == 0);

            if (is_current_user)
            {
                attron(COLOR_PAIR(COLOR_CURRENT_USER) | A_BOLD | A_BLINK);
                mvprintw(y, 10, "*");
                attroff(COLOR_PAIR(COLOR_CURRENT_USER) | A_BOLD | A_BLINK);
            }

            if (i == 0)
            {
                attron(COLOR_PAIR(COLOR_FIRST_SCORE) | A_BOLD | A_ITALIC);
                mvprintw(y - 1, x, "        -----");
                mvprintw(y, x - 1, "(LEGEND) | 1 |  %-15s Score:%5d  Gold: %-4d  XP: %-4d Games: %-4d", 
                         player_username, score, gold, experience, games_number);
                mvprintw(y + 1, x, "        -----");
                attroff(COLOR_PAIR(COLOR_FIRST_SCORE) | A_BOLD | A_ITALIC);
            }
            else if (i == 1)
            {
                attron(COLOR_PAIR(COLOR_SECOND_SCORE) | A_BOLD | A_ITALIC);
                mvprintw(y - 1, x, "        -----");
                mvprintw(y, x - 2, "(WARRIOR) | 2 |  %-15s Score:%5d  Gold: %-4d  XP: %-4d Games: %-4d", 
                         player_username, score, gold, experience, games_number);
                mvprintw(y + 1, x, "        -----");
                attroff(COLOR_PAIR(COLOR_SECOND_SCORE) | A_BOLD | A_ITALIC);
            }
            else if (i == 2)
            {
                attron(COLOR_PAIR(COLOR_THIRD_SCORE) | A_BOLD | A_ITALIC);
                mvprintw(y - 1, x, "        -----");
                mvprintw(y, x - 3, "(CHAMPION) | 3 |  %-15s Score:%5d  Gold: %-4d  XP: %-4d Games: %-4d", 
                         player_username, score, gold, experience, games_number);
                mvprintw(y + 1, x, "        -----");
                attroff(COLOR_PAIR(COLOR_THIRD_SCORE) | A_BOLD | A_ITALIC);
            }
            else
            {
                attron(A_BOLD);
                mvprintw(y, x + 13, "%2d. %-13s Score:%5d  Gold: %-4d  XP: %-4d Games: %-4d", 
                         i + 1, player_username, score, gold, experience, games_number);
                attroff(A_BOLD);
            }
        }

        mvprintw(30, 10, "Use Arrow keys to scroll | Press Q to exit");

        refresh();
        ch = getch();

        if (ch == KEY_UP && current_page > 0)
        {
            current_page--;
        }
        else if (ch == KEY_DOWN && current_page < total_pages - 1)
        {
            current_page++;
        }
        else if (ch == 'q')
        {
            break;
        }
    }

    // Free allocated memory
    for (int i = 0; i < count; i++)
        free(players[i]);
}
