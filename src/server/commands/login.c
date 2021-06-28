/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

static void login_norm(user_t *user, char *uuid)
{
    uuid_generate(user->id);
    uuid_unparse(user->id, uuid);
    server_event_user_created(uuid, user->username);
    server_event_user_logged_in(uuid);
}

int login(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    user_t *user = find_user_by_name(my_team->users, arg[1]);
    char *uuid = malloc(sizeof(char) * 37);

    if (!user) {
        user = malloc(sizeof(user_t));
        user->username = strdup(arg[1]);
        login_norm(user, uuid);
        my_team->users = add_node(my_team->users, user);
        add_user(user->username, user->id);
    } else {
        uuid_unparse(user->id, uuid);
        server_event_user_logged_in(uuid);
    }
    my_team->server.client[i].user = user;
    user->status = 1;
    for (int j = 0; j < 50; ++j)
        if (CLIENT_J.connected && CLIENT_J.user)
            dprintf(CLIENT_J.fd, "600 \"%s\" \"%s\"\n", uuid,
                user->username);
    return (0);
}