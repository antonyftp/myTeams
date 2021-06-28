/*
** EPITECH PROJECT, 2021
** Project
** File description:
** add_thread_reply.c
*/

#include "../../includes/writer.h"

static void fill_file_content_var(char *file_begening, char *file_end,
    char *uuid, FILE *file)
{
    char **splitted_line = NULL;
    int right_thread = 0;
    int end = 0;
    int index = 0;
    char *line = NULL;
    size_t size;

    while (getline(&line, &size, file) != -1) {
        (RIGHT_THREAD) ? right_thread = 1 : 0;
        if (!strcmp(line, "\n") && right_thread)
            update_var(file_begening, &index, &right_thread, &end);
        add_line_to_var((end ? file_end : file_begening), line, &index);
        free_tab(splitted_line);
    }
    if (!end) {
        file_begening[index] = '\0';
        file_end[0] = '\0';
    } else
        file_end[index] = '\0';
}

void find_thread_part(char **beg, char **end, char *uuid)
{
    struct stat st;
    char *file_begenig = NULL;
    char *file_end = NULL;
    FILE *file = open_file(THREAD_PATH, "r");

    if (!file)
        return;
    stat(THREAD_PATH, &st);
    file_begenig = malloc(sizeof(char) * st.st_size * 2);
    file_end = malloc(sizeof(char) * st.st_size * 2);
    fill_file_content_var(file_begenig, file_end, uuid, file);
    fclose(file);
    *beg = file_begenig;
    *end  = file_end;
}

int add_thread_answer(uuid_t uuid, char *username, char *answer,
    time_t timestamp)
{
    char *beg = NULL;
    char *end = NULL;
    FILE *file = NULL;
    char *char_uuid = malloc(sizeof(char) * 37);
    char buf[21];

    uuid_unparse_upper(uuid, char_uuid);
    find_thread_part(&beg, &end, char_uuid);
    file = open_file(THREAD_PATH, "w");
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
    buf[20] = '\0';
    fprintf(file, "%s%s,%s\n%s\n%s", beg, username, answer, buf, end);
    free(char_uuid);
    fclose(file);
    return (0);
}