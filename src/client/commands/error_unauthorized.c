/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client_error_unauthorized_handler.c
*/

#include "client.h"

void client_error_unauthorized_handler(char **args, client_t *client)
{
    if (tab_len(args) == 1)
        client_error_unauthorized();
}
