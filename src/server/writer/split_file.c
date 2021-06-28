/*
** EPITECH PROJECT, 2021
** Project
** File description:
** splt_private_message_file.c
*/

#include "../../includes/writer.h"

void print_file(FILE *file, int new_conv, char *beg, char *names)
{
    fprintf(file, "%s", beg);
    if (!new_conv) {
        if (strcmp(beg, KEY) != 0)
            fprintf(file, "\n");
        fprintf(file, "\n%s", names);
    }
}

char *concat_str(char *str1, char *str2)
{
    char *res = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));

    for (int i = 0; str1[i]; ++i)
        res[i] = str1[i];
    for (int i = 0; str2[i]; ++i)
        res[i + strlen(str1)] = str2[i];
    res[strlen(str1) + strlen(str2)] = '\0';
    return (res);
}

void add_line_to_var(char *file_content, char *line, int *index)
{
    for (int i = 0; line[i]; ++i) {
        file_content[*(index) + i] = line[i];
    }
    (*index) += strlen(line);
}

static void fill_file_content_var(char **file_parts,
    FILE *file, char **names_tab, int *new_conv)
{
    int index = 0;
    int end = 0;
    char *line = NULL;
    int right_conv = 0;
    size_t size;

    file_parts[1][0] = '\0';
    while (getline(&line, &size, file) != -1) {
        if (!strcmp(line, names_tab[0]) || !strcmp(line, names_tab[1])) {
            right_conv = 1;
            *new_conv = 1;
        } else if (!strcmp(line, "\n") && right_conv)
            update_var(file_parts[0], &index, &right_conv, &end);
        add_line_to_var((end ? file_parts[1] : file_parts[0]), line, &index);
    }
    if (*new_conv == 0)
        file_parts[0][index] = '\0';
    file_parts[1][index] = '\0';
}

void find_private_message_part(char **names_tab, char **begening, char **end,
    int *new_conv)
{
    FILE *file = open_file(PRIVATE_MESSAGE_PATH, "r");
    char *file_parts[2];

    struct stat st;

    if (file == (FILE *)-1)
        return;
    stat(PRIVATE_MESSAGE_PATH, &st);
    file_parts[0] = malloc(sizeof(char) * st.st_size * 2);
    file_parts[1] = malloc(sizeof(char) * st.st_size * 2);
    fill_file_content_var(file_parts, file, names_tab, new_conv);
    fclose(file);
    *begening = file_parts[0];
    *end = file_parts[1];
}