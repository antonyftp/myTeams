/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

static int send_error(struct my_teams_t *my_team, char **arg, int i)
{
    dprintf(CLIENT.fd, "613 \"%s\"\n", arg[1]);
    return (-1);
}

int unsubscribed(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    team_t *team;
    uuid_t uuid;
    user_t *user;
    char *user_uuid;

    uuid_parse(arg[1], uuid);
    team = find_team_by_uuid(my_team->teams, uuid);
    if (!team)
        return (send_error(my_team, arg, i));
    user = find_user_by_uuid(team->users, CLIENT.user->id);
    if (user != NULL) {
        user_uuid = malloc(sizeof(char) * 37);
        uuid_unparse(user->id, user_uuid);
        team->users = remove_node(team->users, user);
        dprintf(CLIENT.fd, "628 \"%s\" \"%s\"\n", user_uuid, arg[1]);
        server_event_user_unsubscribed(arg[1], user_uuid);
        team_unsubscribe(team->id, user->username);
        free(user_uuid);
    }
    return (0);
}