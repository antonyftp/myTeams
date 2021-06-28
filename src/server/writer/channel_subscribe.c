/*
** EPITECH PROJECT, 2021
** Project
** File description:
** channel_subscribe.c
*/

#include "../../includes/writer.h"

static void add_right_team(char **splited_line, char *file_begening,
    char *file_end, int *index)
{
    add_line_to_var(file_begening, splited_line[0], index);
    add_line_to_var(file_begening, ";", index);
    add_line_to_var(file_begening, splited_line[1], index);
    add_line_to_var(file_begening, ";", index);
    add_line_to_var(file_begening, splited_line[2], index);
    add_line_to_var(file_begening, ";", index);
    add_line_to_var(file_begening, splited_line[3], index);
    add_line_to_var(file_begening, ",", index);
    file_begening[*index] = '\0';
    *index = 0;
    add_line_to_var(file_end, ";", index);
    add_line_to_var(file_end, splited_line[4], index);
}

static void fill_var(char *file_begening, char *file_end, FILE *file,
    char *uuid)
{
    int index = 0;
    char *line = NULL;
    size_t size;
    int right_team = 0;
    char **splitted_line = NULL;

    getline(&line, &size, file);
    add_line_to_var(file_begening, line, &index);
    while (getline(&line, &size, file) != -1) {
        splitted_line = split_string(strdup(line), ";");
        if (!strcmp(splitted_line[1], uuid)) {
            right_team = 1;
            add_right_team(splitted_line, file_begening, file_end, &index);
        } else {
            add_line_to_var((right_team ? file_end : file_begening), line,
                            &index);
        }
        free_tab(splitted_line);
    }
    file_end[index] = '\0';
}

static void find_file_parts(char **beg, char **end, char *uuid)
{
    FILE *file = open_file(CHANNEL_PATH, "r");
    char *file_begening = NULL;
    char *file_end = NULL;
    struct stat st;

    if (file == (FILE *)-1)
        return;
    stat(CHANNEL_PATH, &st);
    file_begening = malloc(sizeof(char) * st.st_size * 2);
    file_end = malloc(sizeof(char) * st.st_size * 2);
    fill_var(file_begening, file_end, file, uuid);
    fclose(file);
    *beg = file_begening;
    *end = file_end;
}

int channel_subscribe(uuid_t uuid, char *username)
{
    char *beg = NULL;
    char *end = NULL;
    FILE *file = NULL;
    char *char_uuid;

    char_uuid = malloc(sizeof(char) * 37);
    uuid_unparse_upper(uuid, char_uuid);
    find_file_parts(&beg, &end, char_uuid);
    file = open_file(CHANNEL_PATH, "w");
    if (file == (FILE *)-1)
        return (-1);
    fprintf(file, "%s%s%s", beg, username, end);
    free(char_uuid);
    free(end);
    free(beg);
    fclose(file);
    return (0);
}