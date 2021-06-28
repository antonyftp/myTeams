/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client_team_print_channels_handler.c
*/

#include "client.h"

void client_team_print_channels_handler(char **args, client_t *client)
{
    if (tab_len(args) == 4)
        client_team_print_channels(args[1], args[2], args[3]);
}