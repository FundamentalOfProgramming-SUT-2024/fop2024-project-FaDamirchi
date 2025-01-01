#include "manage_users.h"
#include "ui_utils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

bool is_email_valid(int start_y, int start_x, char *email)
{
    if (!email || strlen(email) == 0)
    {
        show_alert_message(start_y, start_x, "Please provide a valid email address.");
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
        show_alert_message(start_y, start_x, "Please provide a valid email address.");
        return false;
    }

    // '@' cannot be the first or the last character
    if (atIndex == 0 || atIndex == len - 1)
    {
        show_alert_message(start_y, start_x, "Please provide a valid email address.");
        return false;
    }

    // '.' cannot be immidiately after '@'
    if (dotIndex == atIndex + 1)
    {
        show_alert_message(start_y, start_x, "Please provide a valid email address.");
        return false;
    }

    // check characters in local part
    for (int i = 0; i < atIndex; i++)
    {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '_' && email[i] != '-')
        {
            show_alert_message(start_y, start_x, "Please provide a valid email address.");
            return false;
        }
    }

    // check characters in domain part
    for (int i = atIndex + 1; i < len; i++)
    {
        if (!isalnum(email[i]) && email[i] != '.' && email[i] != '-')
        {
            show_alert_message(start_y, start_x, "Please provide a valid email address.");
            return false;
        }
    }

    // domain part must have at least one dot
    if (dotIndex < atIndex)
    {
        show_alert_message(start_y, start_x, "Please provide a valid email address.");
        return false;
    }

    return true;
}

bool is_email_unique(int start_y, int start_x, char *email)
{
    FILE *file = fopen(USERS_FILE, "r");

    char line[256];

    while (fgets(line, sizeof(line), file))
    {
        char saved_email[320];
        sscanf(line, "%[^:]", saved_email);

        if (strcmp(saved_email, email) == 0)
        {
            show_alert_message(start_y, start_x, "Email already exists.");
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

    char line[256];

    while (fgets(line, sizeof(line), file))
    {
        char saved_username[64];
        sscanf(line, "%*[^:]:%[^:]", saved_username);

        if (strcmp(saved_username, username) == 0)
        {
            show_alert_message(start_y, start_x, "Username already exists.");
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
        show_alert_message(start_y, start_x, "Please choose a password.");
        return false;
    }

    int digCount = 0; // number of digits
    int uprCount = 0; // number of capital letters
    int lwrCount = 0; // number of small letters

    int len = strlen(password);

    if (len < 7)
    {
        show_alert_message(start_y, start_x, "Password is too short. (Minimum length is 7)");
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
        show_alert_message(start_y, start_x, "Password must contain at least one digit.");
        return false;
    }

    if (uprCount == 0)
    {
        show_alert_message(start_y, start_x, "Password must contain at least one capital letter.");
        return false;
    }

    if (lwrCount == 0)
    {
        show_alert_message(start_y, start_x, "Password must contain at least one small letter.");
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

    srand(time(NULL));

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
    FILE *file = fopen(USERS_FILE, "a");
    fprintf(file, "%s:%s:%s\n", email, username, password);
    fclose(file);
}