/*
** EPITECH PROJECT, 2021
** MyTeams
** File description:
** is_uuid.c
*/

#include "server.h"

static bool is_hexa_char(char c)
{
    char *ref = "abcdefABCDEF0123456789";

    for (int i = 0; ref[i]; ++i)
        if (c == ref[i])
            return (true);
    return (false);
}

bool is_uuid(char *uuid)
{
    if (strlen(uuid) != 36)
        return (false);
    for (int i = 0; uuid[i]; ++i) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (uuid[i] != '-')
                return (false);
        } else
            if (!is_hexa_char(uuid[i]))
                return (false);
    }
    return (true);
}