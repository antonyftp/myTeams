/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** create_file
*/

#include "server.h"

void *create_file(char *filepath)
{
    FILE *file = fopen(filepath, "w");

    fprintf(file, "%s", KEY);
    fclose(file);
    return (NULL);
}