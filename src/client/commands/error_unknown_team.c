/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client_error_unknown_team_handler.c
*/

#include "client.h"

void client_error_unknown_team_handler(char **args, client_t *client)
{
    if (tab_len(args) == 2)
        client_error_unknown_team(args[1]);
}