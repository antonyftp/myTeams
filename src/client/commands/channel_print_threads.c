/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client_channel_print_threads_handler.c
*/

#include "client.h"

void client_channel_print_threads_handler(char **args, client_t *client)
{
    if (tab_len(args) == 6)
        client_channel_print_threads(args[1], args[2], char_to_time(
        args[3]), args[4], args[5]);
}