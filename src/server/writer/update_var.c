/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** Created by antonyftp
*/

#include "writer.h"

void update_var(char *file_begening, int *index, int *right,
    int *end)
{
    *end = 1;
    file_begening[*index] = '\0';
    *index = 0;
    *right = 0;
}