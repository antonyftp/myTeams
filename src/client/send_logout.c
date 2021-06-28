/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** send_logout
*/

#include "client.h"

void send_logout(client_t *client, char *command, char **splited_commmand)
{
    if (tab_len(splited_commmand) == 1) {
        dprintf(client->socket_fd, "%s\n", command);
        return;
    }
    printf(AGRS_NOT_IMPLEMENTED, splited_commmand[0]);
}