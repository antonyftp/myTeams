/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

int users(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    user_list_t *users = my_team->users;
    user_t *user = NULL;
    char *uuid = malloc(37);

    for (;users != NULL; users = users->next) {
        user = (user_t *)users->data;
        uuid_unparse(user->id, uuid);
        dprintf(my_team->server.client[i].fd, "607 \"%s\" \"%s\" \"%i\"\n",
            uuid, user->username, user->status);
    }
    free(uuid);
    return (0);
}