/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** disconnect
*/

#include "server.h"

static void do_disconnect(struct my_teams_t *my_team, int i)
{
    char *uuid;

    if (my_team->server.client[i].fd > 0) {
        if (my_team->server.client[i].user != NULL) {
            uuid = malloc(sizeof(char) * 37);
            uuid_unparse(my_team->server.client[i].user->id, uuid);
            my_team->server.client[i].user->status = 0;
            dprintf(my_team->server.client[i].fd, "601 \"%s\" \"%s\"\n",
                uuid, my_team->server.client[i].user->username);
            dprintf(my_team->server.client[i].fd, "200\n");
            free(uuid);
        } else
            dprintf(my_team->server.client[i].fd, "629\n");
        my_team->server.client[i].fd = -1;
        my_team->server.client[i].user = NULL;
        my_team->server.client[i].use_status = Nothing;
        my_team->server.client[i].connected = false;
    }
}

void disconnect(struct my_teams_t *my_team)
{
    for (int i = 0; i < CLIENT_MAX; i++)
        do_disconnect(my_team, i);
}