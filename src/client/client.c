/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** client
*/

#include "client.h"

static int set_select(int socket_fd, fd_set *rdfs)
{
    FD_ZERO(rdfs);
    FD_SET(STDIN_FILENO, rdfs);
    FD_SET(socket_fd, rdfs);
    if (select(socket_fd + 1, rdfs, NULL, NULL, NULL) == -1)
        return (-1);
    return (0);
}

int client(char *ip, int port)
{
    client_t client;
    fd_set rdfs;
    char *buf = NULL;

    new_client(&client, init_connection(ip, port));
    if (client.socket_fd == -1)
        return (0);
    while (client.quit) {
        if (set_select(client.socket_fd, &rdfs) == -1)
            return (1);
        if (handle_client(&rdfs, &client))
            return (1);
    }
    return (0);
}