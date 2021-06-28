/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client_private_message_print_messages_handler.c
*/

#include "client.h"

void client_private_message_print_messages_handler(char **args,
    client_t *client)
{
    if (tab_len(args) == 4)
        client_private_message_print_messages(args[1], char_to_time(args[2]),
            args[3]);
}