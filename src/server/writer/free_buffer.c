/*
** EPITECH PROJECT, 2021
** MyTeams
** File description:
** free_private_message_buf.c
*/

#include "writer.h"

int free_buf(char *end, FILE *file, char *beg)
{
    if (!end[0])
        fprintf(file, "\n%s", end);
    fclose(file);
    free(beg);
    free(end);
    return (0);
}