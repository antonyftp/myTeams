/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

int logout(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    char *uuid = malloc(sizeof(char) * 37);

    uuid_unparse(my_team->server.client[i].user->id, uuid);
    for (int j = 0; j < 50; ++j)
        if (my_team->server.client[j].connected
            && my_team->server.client[j].user)
        dprintf(my_team->server.client[j].fd, "601 \"%s\" \"%s\"\n", uuid,
            my_team->server.client[i].user->username);
    server_event_user_logged_out(uuid);
    dprintf(my_team->server.client[i].fd, "200\n");
    if (CLIENT.user) {
        my_team->server.client[i].user->status = 0;
        my_team->server.client[i].fd = 0;
        my_team->server.client[i].user = NULL;
    }
    my_team->server.client[i].use_status = Nothing;
    my_team->server.client[i].connected = false;
    free(uuid);
    return (0);
}