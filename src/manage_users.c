#include "manage_users.h"
#include "global_defines.h"

bool is_email_valid(int start_y, int start_x, char *email)
{
    if (!email || strlen(email) == 0)
    {
        show_alert_message(start_y, start_x, "Please provide a valid email address.", 2);
        return false;
    }

    int atCount = 0;   // number of @
    int atIndex = -1;  // index of @
    int dotCount = 0;  // number of .
    int dotIndex = -1; // index of .

    int len = strlen(email);

    for (int i = 0; i < len; i++)
    {
        if (email[i] == '@')
        {
            atCount++;
            atIndex = i;
        }
        else if (email[i] == '.')
        {
            dotCount++;
            dotIndex = i;
        }
    }

    // must have exactly one '@' and at least one '.'
    if (atCount != 1 || dotCount < 1)
    {
        show_alert_message(start_y, start_x, "Please provide a valid email address.", 2);
        return false;
    }

    // '@' cannot be the first or the last character
    if (atIndex == 0 || atIndex == len - 1)
    {
        show_alert_message(start_y, start_x, "Please provide a valid email address.", 2);
        return false;
    }

    // '.' cannot be immidiately after '@'
    if (dotIndex == atIndex + 1)
    {
        show_alert_message(start_y, start_x, "Please provide a valid email address.", 2);
        return false;
    }

    // check characters in local part
    for (int i = 0; i < atIndex; i++)
    {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '_' && email[i] != '-')
        {
            show_alert_message(start_y, start_x, "Please provide a valid email address.", 2);
            return false;
        }
    }

    // check characters in domain part
    for (int i = atIndex + 1; i < len; i++)
    {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '-')
        {
            show_alert_message(start_y, start_x, "Please provide a valid email address.", 2);
            return false;
        }
    }

    // domain part must have at least one dot
    if (dotIndex < atIndex)
    {
        show_alert_message(start_y, start_x, "Please provide a valid email address.", 2);
        return false;
    }

    return true;
}

bool is_email_unique(int start_y, int start_x, char *email)
{
    FILE *file = fopen(USERS_FILE, "r");

    char line[1024];

    while (fgets(line, sizeof(line), file))
    {
        char saved_email[320];
        sscanf(line, "%[^:]", saved_email);

        if (strcmp(saved_email, email) == 0)
        {
            show_alert_message(start_y, start_x, "Email already exists.", 2);
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}

bool is_username_unique(int start_y, int start_x, char *username)
{
    FILE *file = fopen(USERS_FILE, "r");

    char line[1024];

    while (fgets(line, sizeof(line), file))
    {
        char saved_username[64];
        sscanf(line, "%*[^:]:%[^:]", saved_username);

        if (strcmp(saved_username, username) == 0)
        {
            show_alert_message(start_y, start_x, "Username already exists.", 2);
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}

bool is_password_valid(int start_y, int start_x, char *password)
{
    if (!password || strlen(password) == 0)
    {
        show_alert_message(start_y, start_x, "Please choose a password.", 1.5);
        return false;
    }

    int digCount = 0; // number of digits
    int uprCount = 0; // number of capital letters
    int lwrCount = 0; // number of small letters

    int len = strlen(password);

    if (len < 7)
    {
        show_alert_message(start_y, start_x, "Password is too short. (Minimum length is 7)", 2.5);
        return false;
    }

    for (int i = 0; i < len; i++)
    {
        if (isdigit(password[i]))
        {
            digCount++;
        }
        else if (isupper(password[i]))
        {
            uprCount++;
        }
        else if (islower(password[i]))
        {
            lwrCount++;
        }
    }

    if (digCount == 0)
    {
        show_alert_message(start_y, start_x, "Password must contain at least one digit.", 2.5);
        return false;
    }

    if (uprCount == 0)
    {
        show_alert_message(start_y, start_x, "Password must contain at least one capital letter.", 2.5);
        return false;
    }

    if (lwrCount == 0)
    {
        show_alert_message(start_y, start_x, "Password must contain at least one small letter.", 2.5);
        return false;
    }

    return true;
}

void generate_password(char *password)
{
    const char all[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$\%^&*-+/";
    const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char digit[] = "0123456789";

    int length = 7 + (rand() % 10);

    password[0] = lowercase[rand() % 26];
    password[1] = uppercase[rand() % 26];
    password[2] = digit[rand() % 26];

    for (int i = 3; i < length; i++)
    {
        password[i] = all[rand() % sizeof(all)];
    }

    // shuffel the password
    for (int i = 0; i < length; i++)
    {
        int j = rand() % length;
        char temp = password[i];
        password[i] = password[j];
        password[j] = temp;
    }

    password[length] = '\0';
}

void create_new_user(char *email, char *username, char *password)
{
    // add identity
    FILE *file = fopen(USERS_FILE, "a");
    fprintf(file, "%s:%s:%s\n", email, username, password);
    fclose(file);

    // add default settings
    file = fopen(SETTINGS_FILE, "a");
    fprintf(file, "%s:%d-%d-%d\n", username, 1, 1, 1);
    fclose(file);

    file = fopen(USERS_FILE, "a");
    fprintf(file, "%s:%d-%d-%d", username, 0, 0, 0);
    fclose(file);
}

int authenticate_user(char *username, char *password)
{
    FILE *file = fopen(USERS_FILE, "r");

    char line[1024];

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        char stored_username[64];
        char stored_password[64];

        if (sscanf(line, "%*[^:]:%[^:]:%s", stored_username, stored_password) == 2)
        {
            if (strcmp(username, stored_username) == 0)
            {
                if (strcmp(password, stored_password) == 0)
                {
                    fclose(file);
                    return SUCCESSFULL_LOGIN;
                }
                else
                {
                    fclose(file);
                    return INCORRECT_PASSWORD;
                }
            }
        }
    }

    fclose(file);
    return USERNAME_NOT_FOUND;
}

void password_recovery(char *username, char *email, int start_y, int start_x)
{
    FILE *file = fopen(USERS_FILE, "r");

    char line[1024];

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        char stored_email[320];
        char stored_username[64];
        char stored_password[64];

        if (sscanf(line, "%[^:]:%[^:]:%s", stored_email, stored_username, stored_password) == 3)
        {
            if (strcmp(username, stored_username) == 0)
            {
                if (strcmp(email, stored_email) == 0)
                {
                    show_success_message(start_y, start_x, "Password recovered successfully!", 1);

                    char recovered_password[124];
                    strcpy(recovered_password, "Your password is: ");
                    strcat(recovered_password, stored_password);

                    show_success_message(start_y + 1, start_x, recovered_password, 1);

                    show_success_message(start_y + 3, start_x, "Use this password to login again.", 1);
                    show_alert_message(start_y + 5, start_x, "Press any key to continue...", 0);
                    getch();

                    fclose(file);
                }
                else
                {
                    show_alert_message(start_y, start_x, "Password recovery failed!", 2);

                    fclose(file);
                }
            }
        }
    }
}

void update_score(char *username, int score, int gold, int experience, int games_number)
{
    FILE *file = fopen(SCORES_FILE, "r");

    char line[1024];
    int stored_score;
    int stored_gold;
    int stored_experience;
    int stored_games_number;

    while (fgets(line, sizeof(line), file))
    {
        char stored_username[320];
        sscanf(line, "%[^:]:", stored_username);

        if (strcmp(stored_username, username) == 0)
        {
            sscanf(line, "%*[^:]:%d-%d-%d-%d", &stored_score, &stored_gold, &stored_experience, &stored_games_number);
            break;
        }
    }

    fclose(file);


    file = fopen(SCORES_FILE, "r+");
    if (!file)
    {
        perror("Error opening settings file");
        return;
    }

    // create a temp file to store changes in it
    char temp_file_name[] = "temp_scores.txt";
    FILE *temp_file = fopen(temp_file_name, "w");

    while (fgets(line, sizeof(line), file))
    {
        char stored_username[320];
        sscanf(line, "%[^:]:", stored_username);

        if (strcmp(stored_username, username) == 0)
        {
            // update the settings for the user
            fprintf(temp_file, "%s:%d-%d-%d-%d\n", username, stored_score + score,
                                                          stored_gold + gold,
                                                          stored_experience + experience,
                                                          stored_games_number + games_number);
        }
        else
        {
            // copy the line in the main file
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    // replace the old file with the updated file
    remove(SCORES_FILE);
    rename(temp_file_name, SCORES_FILE);
}