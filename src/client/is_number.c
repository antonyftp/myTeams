/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** isnumber
*/

#include "client.h"

int is_number(char *str)
{
    for (int i = 0; str[i]; ++i)
        if (str[i] < '0' || str[i] > '9')
            return (0);
    return (1);
}