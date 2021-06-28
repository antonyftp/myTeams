/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client_event_private_message_received_handler.c
*/

#include "client.h"

void client_event_private_message_received_handler(char **args,
    client_t *client)
{
    if (tab_len(args) == 3)
        client_event_private_message_received(args[1], args[2]);
}