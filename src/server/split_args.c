/*
** EPITECH PROJECT, 2021
** MyTeams
** File description:
** split_args..c
*/

#include "client.h"

static char **create_empty_tab(int size)
{
    char **args_tab = malloc(sizeof(char *) * (size));

    for (int i = 0; i < size; ++i)
        args_tab[i] = NULL;
    return (args_tab);
}

static void condition(int first, char **args_tab, int *index,
    int *current_index)
{
    if (first) {
        args_tab[*index][*current_index] = '\0';
        ++(*index);
    }
    *current_index = 0;
}

static int end_condition(char *args, int *arg_index, char **args_tab,
    int *index)
{
    if (args[*arg_index + 1] != '\0')
        args_tab[*index] = malloc(sizeof(char) * strlen(args));
    return (0);
}

static void fill_args(char **args_tab, char *args, int *index,
    int *arg_index)
{
    int first = 0;
    int current_index = 0;

    if (args[*arg_index] == '\0')
        return;
    args_tab[*index] = malloc(sizeof(char) * strlen(args));
    for (; args[*arg_index]; ++(*arg_index)) {
        if (args[*arg_index] == ' ' && !first)
            continue;
        else if (args[*arg_index] == '"') {
            condition(first, args_tab, index, &current_index);
            (first ? end_condition(args, arg_index, args_tab, index) : 1);
            first = !first;
        } else {
            args_tab[*index][current_index++] = args[*arg_index];
        }
    }
}

char **split_args(char *args)
{
    int sep_number = 0;
    char **args_tab = NULL;
    int index = 0;
    int arg_index = 0;

    for (int i = 0; args[i]; ++i)
        (args[i] == '"') ? ++sep_number : 0;
    args_tab = create_empty_tab(sep_number + 2);
    if (sep_number % 2) {
        free(args_tab);
        return (NULL);
    }
    while (sep_number && args[strlen(args) - 1] != '"')
        args[strlen(args) - 1] = '\0';
    args_tab[index] = malloc(sizeof(char) * (strlen(args) + 1));
    for (; args[arg_index] && args[arg_index] != ' '; ++arg_index)
        args_tab[index][arg_index] = args[arg_index];
    args_tab[index++][arg_index] = '\0';
    fill_args(args_tab, args, &index, &arg_index);
    return (args_tab);
}