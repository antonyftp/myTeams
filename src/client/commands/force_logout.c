/*
** EPITECH PROJECT, 2021
** MyTeams
** File description:
** force_logout.c
*/

#include "client.h"

void force_logout(char **args, client_t *client)
{
    if (tab_len(args) == 1)
        client->quit = QUIT;
}