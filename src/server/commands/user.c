/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

int user(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    user_t *user;
    user_list_t *users = my_team->users;
    uuid_t uuid;

    uuid_parse(arg[1], uuid);
    user = find_user_by_uuid(users, uuid);
    if (user == NULL) {
        dprintf(my_team->server.client[i].fd, "616 \"%s\"\n", arg[1]);
        return (-1);
    }
    dprintf(my_team->server.client[i].fd, "619 \"%s\" \"%s\" \"%i\"\n", arg[1],
        user->username, user->status);
    return (0);
}