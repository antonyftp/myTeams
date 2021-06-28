/*
** EPITECH PROJECT, 2021
** Project
** File description:
** add_user.c
*/

#include "../../includes/writer.h"

int add_user(char *username, uuid_t uuid)
{
    FILE *file = open_file(USER_PATH, "a");
    char *char_uuid;

    if (file == (FILE *)-1)
        return (-1);
    char_uuid = malloc(sizeof(char) * 37);
    uuid_unparse_upper(uuid, char_uuid);
    fprintf(file, "\n%s;%s", username, char_uuid);
    fclose(file);
    free(char_uuid);
    return (0);
}

int add_thread(char *title, uuid_t uuid, char *owner, char *message)
{
    FILE *file = open_file(THREAD_PATH, "a");
    char *char_uuid;
    char buf[21];
    time_t timer = time(NULL);

    if (file == (FILE *)-1)
        return (-1);
    char_uuid = malloc(sizeof(char) * 37);
    uuid_unparse_upper(uuid, char_uuid);
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", localtime(&timer));
    buf[20] = '\0';
    fprintf(file, "\n%s;%s;%s;%s;%s\n", title, char_uuid, owner, buf, message);
    fclose(file);
    free(char_uuid);
    return (0);
}

int add_team(char *title, uuid_t uuid, char *description, char *owner)
{
    FILE *file = open_file(TEAM_PATH, "a");
    char *char_uuid;

    if (file == (FILE *)-1)
        return (-1);
    char_uuid = malloc(sizeof(char) * 37);
    uuid_unparse_upper(uuid, char_uuid);
    fprintf(file, "\n%s;%s;%s;%s;", title, char_uuid, description, owner);
    fclose(file);
    free(char_uuid);
    return (0);
}

int add_channel(char *title, uuid_t uuid, char *description)
{
    FILE *file = open_file(CHANNEL_PATH, "a");
    char *char_uuid;

    if (file == (FILE *)-1)
        return (-1);
    char_uuid = malloc(sizeof(char) * 37);
    uuid_unparse_upper(uuid, char_uuid);
    fprintf(file, "\n%s;%s;%s;", title, char_uuid, description);
    fclose(file);
    free(char_uuid);
    return (0);
}

int add_private_message(char *first, char *second, char *message,
                        time_t timestamp)
{
    char *beg = NULL;
    char *end = NULL;
    FILE *file = NULL;
    char buf[21];
    int new_conv = 0;
    char *names_tab[2] = { concat_str(concat_str(first, concat_str("-",
        second)), "\n"), concat_str(concat_str(second,
        concat_str("-", first)), "\n") };

    find_private_message_part(names_tab, &beg, &end, &new_conv);
    file = open_file(PRIVATE_MESSAGE_PATH, "w");
    if (file == (FILE *)-1)
        return (-1);
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
    buf[20] = '\0';
    print_file(file, new_conv, beg, names_tab[0]);
    fprintf(file, "%s:%s\n%s", first, message, buf);
    return (free_buf(end, file, beg));
}