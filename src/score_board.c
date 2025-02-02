#include "score_board.h"
#include "global_defines.h"
#include "manage_users.h"

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
    clear();

    for (int i = 0; i < count; i++)
    {
        int y = 5 + i * 4;
        int x = 15; // Center alignment

        char player_username[320];
        int score, gold, experience, games_number;
        sscanf(players[i], "%319[^:]:%d-%d-%d-%d", player_username, &score, &gold, &experience, &games_number);

        // Check if this is the current user
        bool is_current_user = false;;
        if (username != NULL)
        {
            is_current_user = (strcmp(player_username, username) == 0);
        }

        // Set background color if the current user is being displayed
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
            mvprintw(y, x, "        | 1 |  %-15s Score:%5d  Gold: %-4d  Experience: %-4d Total Games: %-4d", player_username, 
                                                                                                             score, gold, 
                                                                                                             experience, games_number);
            mvprintw(y + 1, x, "        -----");
            attroff(COLOR_PAIR(COLOR_FIRST_SCORE) | A_BOLD | A_ITALIC);
        }
        else if (i == 1)
        {
            attron(COLOR_PAIR(COLOR_SECOND_SCORE) | A_BOLD | A_ITALIC);
            mvprintw(y - 1, x, "        -----");
            mvprintw(y, x, "        | 2 |  %-15s Score:%5d  Gold: %-4d  Experience: %-4d Total Games: %-4d", player_username,
                                                                                                             score, gold,
                                                                                                             experience, games_number);
            mvprintw(y + 1, x, "        -----");
            attroff(COLOR_PAIR(COLOR_SECOND_SCORE) | A_BOLD | A_ITALIC);
        }
        else if (i == 2)
        {
            attron(COLOR_PAIR(COLOR_THIRD_SCORE) | A_BOLD | A_ITALIC);
            mvprintw(y - 1, x, "        -----");
            mvprintw(y, x, "        | 3 |  %-15s Score:%5d  Gold: %-4d  Experience: %-4d Total Games: %-4d", player_username, 
                                                                                                             score, gold, 
                                                                                                             experience, games_number);
            mvprintw(y + 1, x, "        -----");
            attroff(COLOR_PAIR(COLOR_THIRD_SCORE) | A_BOLD | A_ITALIC);
        }
        else
        {
            attron(A_BOLD);
            mvprintw(y, x + 13, "%2d. %-13s Score:%5d  Gold: %-4d  Experience: %-4d Total Games: %-4d", i + 1, player_username, 
                                                                                                               score, gold, 
                                                                                                               experience, games_number);
            attroff(A_BOLD);
        }
    }

    mvprintw(30, 0, "Press any key to return...");
    refresh();
    getch();

    // Free allocated memory
    for (int i = 0; i < count; i++)
        free(players[i]);
}
