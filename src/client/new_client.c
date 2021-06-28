/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** new_client
*/

#include "client.h"

void new_client(client_t *client, int socket_fd)
{
    client->socket_fd = socket_fd;
    client->is_loggin = NOT_LOGGEDIN;
    client->quit = CONTINUE;
}