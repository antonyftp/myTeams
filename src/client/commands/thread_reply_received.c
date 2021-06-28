/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client_event_thread_reply_received_handler.c
*/

#include "client.h"

void client_event_thread_reply_received_handler(char **args, client_t *client)
{
    if (tab_len(args) == 5)
        client_event_thread_reply_received(args[1], args[2], args[3], args[4]);
}