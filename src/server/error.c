/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** error
*/

#include "../../includes/server.h"

int check_port(char *port)
{
    for (size_t i = 0; i < strlen(port); i++) {
        if (isalpha(port[i]))
            return (1);
    }
    return (0);
}