/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** Created by antonyftp
*/

#include "utils.h"

FILE *open_file(char *filepath, char *mode)
{
    if (check_file(filepath) == -1)
        return ((FILE *)-1);
    FILE *file = fopen(filepath, mode);
    if (!file)
        return ((FILE *)-1);
    return (file);
}

int check_file(char *filepath)
{
    FILE *file = fopen(filepath, "r");
    int ret_val = 0;
    char *line = NULL;
    size_t n = 0;

    if (!file)
        return (-1);
    ret_val = getline(&line, &n, file);
    if (ret_val == -1 || (ret_val == 1
        && strcmp(KEY, line) != 0)) {
        fclose(file);
        return (-1);
    }
    fclose(file);
    return (0);
}

char **split_string(char *str, char *tok)
{
    char *token = strtok(str, tok);
    char **tab = malloc(sizeof(char *));

    if (!str || !tab || !token || strlen(str) == 0)
        return (NULL);
    for (int i = 0; 1; ) {
        tab[i++] = strdup(token);
        tab = realloc(tab, (sizeof(char *) * (i + 1)));
        token = strtok(NULL, tok);
        if (token == NULL) {
            tab[i] = token;
            break;
        }
    }
    free(token);
    return (tab);
}

void free_tab(char **tab)
{
    for (int i = 0; tab[i]; ++i)
        free(tab[i]);
    free(tab);
}

int tab_len(char **tab)
{
    int len = 0;

    if (tab == NULL)
        return (0);
    for (; tab[len]; ++len);
    return (len);
}