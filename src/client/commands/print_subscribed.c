/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client_print_subscribed_handler.c
*/

#include "client.h"

void client_print_subscribed_handler(char **args, client_t *client)
{
    if (tab_len(args) == 3)
        client_print_subscribed(args[1], args[2]);
}