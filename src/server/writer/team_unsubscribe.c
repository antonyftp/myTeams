/*
** EPITECH PROJECT, 2021
** Project
** File description:
** team_unsubscribe.c
*/

#include "../../includes/writer.h"

static void add_right_team(char **splited_line, char *file_begening, int *index,
    char *username)
{
    char **usernames = split_string(splited_line[3], ",");

    add_line_to_var(file_begening, splited_line[0], index);
    add_line_to_var(file_begening, ";", index);
    add_line_to_var(file_begening, splited_line[1], index);
    add_line_to_var(file_begening, ";", index);
    add_line_to_var(file_begening, splited_line[2], index);
    add_line_to_var(file_begening, ";", index);
    for (int i = 0; i < tab_len(usernames); ++i) {
        if (strcmp(usernames[i], username) != 0) {
            i != 0 ? add_line_to_var(file_begening, ",", index) : NULL;
            add_line_to_var(file_begening, usernames[i], index);
        }
    }
    add_line_to_var(file_begening, ";", index);
    add_line_to_var(file_begening, splited_line[4], index);
}

static void fill_var(char *file_begening, FILE *file, char *uuid,
    char *username)
{
    int index = 0;
    char *line = NULL;
    size_t size;
    char **splitted_line = NULL;

    getline(&line, &size, file);
    add_line_to_var(file_begening, line, &index);
    while (getline(&line, &size, file) != -1) {
        splitted_line = split_string(strdup(line), ";");
        if (!strcmp(splitted_line[1], uuid)) {
            add_right_team(splitted_line, file_begening, &index, username);
        } else {
            add_line_to_var(file_begening, line, &index);
        }
        free_tab(splitted_line);
    }
    file_begening[index] = '\0';
}

static void find_file_parts(char **beg, char *uuid, char *username)
{
    FILE *file = open_file(TEAM_PATH, "r");
    char *file_begening = NULL;
    struct stat st;

    if (file == (FILE *)-1)
        return;
    stat(TEAM_PATH, &st);
    file_begening = malloc(sizeof(char) * st.st_size * 2);
    fill_var(file_begening, file, uuid, username);
    fclose(file);
    *beg = file_begening;
}

int team_unsubscribe(uuid_t uuid, char *username)
{
    char *beg = NULL;
    FILE *file = NULL;
    char *char_uuid;

    char_uuid = malloc(sizeof(char) * 37);
    uuid_unparse_upper(uuid, char_uuid);
    find_file_parts(&beg, char_uuid, username);
    file = open_file(TEAM_PATH, "w");
    if (file == (FILE *)-1)
        return (-1);
    fprintf(file, "%s", beg);
    free(char_uuid);
    free(beg);
    fclose(file);
    return (0);
}