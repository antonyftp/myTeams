/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** init
*/

#include "../../includes/server.h"

void init_client(struct client_t *client, int receive)
{
    client->fd = receive;
    client->connected = true;
    client->use_status = Nothing;
}