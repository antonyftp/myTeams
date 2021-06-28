/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** handle_client
*/

#include "client.h"

static int input(fd_set *rdfs, client_t *client)
{
    char *buf = NULL;
    char *command = NULL;
    size_t n;

    if (FD_ISSET(STDIN_FILENO, rdfs)) {
        if (getline(&buf, &n, stdin) == -1)
            return (1);
        buf[strlen(buf) - 1] = '\0';
        command = strdup(buf);
        if (buf == (char *) -1) {
            return (1);
        }
        if (buf[0]) {
            send_command(client, command, split_args(buf));
        }
        free(buf);
        free(command);
    }
    return (0);
}

static int outpt(fd_set *rdfs, client_t *client)
{
    char *buf = NULL;
    char *command = NULL;

    if (FD_ISSET(client->socket_fd, rdfs)) {
        buf = get_line(client->socket_fd);
        command = strdup(buf);
        if (buf == (char *) -1) {
            return (1);
        }
        if (buf[0]) {
            read_command(client, command, split_args(buf));
        }
        free(buf);
        free(command);
    }
    return (0);
}

int handle_client(fd_set *rdfs, client_t *client)
{
    char *buf = NULL;
    char *command = NULL;

    if (input(rdfs, client))
        return (1);
    if (outpt(rdfs, client))
        return (1);

    free(buf);
    free(command);
    return (0);
}