/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

static int end_subscribe(char **arg, char *user_uuid,
    struct my_teams_t *my_team, int i)
{
    server_event_user_subscribed(arg[1], user_uuid);
    dprintf(my_team->server.client[i].fd, "627 \"%s\" \"%s\"\n", user_uuid,
            arg[1]);
    free(user_uuid);
    return (0);
}

int subscribe(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    team_t *team = NULL;
    uuid_t uuid;
    char *user_uuid = NULL;

    uuid_parse(arg[1], uuid);
    team = find_team_by_uuid(my_team->teams, uuid);
    if (!team) {
        dprintf(my_team->server.client[i].fd, "613\n");
        return (-1);
    }
    if (find_user_by_uuid(team->users, my_team->server.client[i].user->id))
        return (-1);
    user_uuid = malloc(sizeof(char) * 37);
    uuid_unparse(my_team->server.client[i].user->id, user_uuid);
    team->users = add_node(team->users, my_team->server.client[i].user);
    team_subscribe(uuid, my_team->server.client[i].user->username);
    return (end_subscribe(arg, user_uuid, my_team, i));
}