/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client_thread_print_replies_handler.c
*/

#include "client.h"

void client_thread_print_replies_handler(char **args, client_t *client)
{
    if (tab_len(args) == 5)
        client_thread_print_replies(args[1], args[2], char_to_time(args[3]),
            args[4]);
}