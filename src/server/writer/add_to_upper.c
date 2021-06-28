/*
** EPITECH PROJECT, 2021
** Project
** File description:
** add_thread_channel_to_upper.c
*/

#include "../../includes/writer.h"

static void add_line(char *file_begening, char *file_end, char *line,
    int *index)
{
    int do_it = 0;

    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
        do_it = 1;
    }
    add_line_to_var(file_begening, line, index);
    if (line[strlen(line) - 1] != ';')
        add_line_to_var(file_begening, ",", index);
    file_begening[*index] = '\0';
    *index = 0;
    if (do_it == 1)
        add_line_to_var(file_end, "\n", index);
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
            add_line(file_begening, file_end, line, &index);
        } else {
            add_line_to_var((right_team ? file_end : file_begening), line,
                            &index);
        }
        free_tab(splitted_line);
    }
    file_end[index] = '\0';
}

static void find_file_parts(char **beg, char **end, char *uuid, char *filepath)
{
    FILE *file = open_file(filepath, "r");
    char *file_begening = NULL;
    char *file_end = NULL;
    struct stat st;

    if (file == (FILE *)-1)
        return;
    stat(TEAM_PATH, &st);
    file_begening = malloc(sizeof(char) * st.st_size * 2);
    file_end = malloc(sizeof(char) * st.st_size * 2);
    fill_var(file_begening, file_end, file, uuid);
    fclose(file);
    *beg = file_begening;
    *end = file_end;
}

void add_thread_channel_to_upper(char *filepath, uuid_t uuid, uuid_t child_uuid)
{
    char *beg = NULL;
    char *end = NULL;
    FILE *file = NULL;
    char *char_uuid;
    char *char_child_uuid;

    char_uuid = malloc(sizeof(char) * 37);
    uuid_unparse_upper(uuid, char_uuid);
    char_child_uuid = malloc(sizeof(char) * 37);
    uuid_unparse_upper(child_uuid, char_child_uuid);
    find_file_parts(&beg, &end, char_uuid, filepath);
    file = open_file(filepath, "w");
    if (file == (FILE *)-1)
        return;
    fprintf(file, "%s%s%s", beg, char_child_uuid, end);
    free(char_uuid);
    free(char_child_uuid);
    free(end);
    free(beg);
    fclose(file);
}