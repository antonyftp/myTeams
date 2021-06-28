/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

static void show_subscribed_team(struct my_teams_t *my_team, int i)
{
    team_list_t *list = my_team->teams;
    team_t *team = NULL;
    char *uuid;

    for (; list; list = list->next) {
        team = (team_t *)list->data;
        if (find_user_by_uuid(team->users,
            my_team->server.client[i].user->id) != NULL) {
            uuid = malloc(sizeof(char) * 37);
            uuid_unparse(team->id, uuid);
            dprintf(my_team->server.client[i].fd, "608 \"%s\" \"%s\" \"%s\"\n",
                    uuid, team->title, team->description);
            free(uuid);
        }
    }
}

static void print_all_users(struct my_teams_t *my_team, team_t *team, int i)
{
    char *uuid_user;
    user_list_t *user_list = team->users;

    for (; user_list; user_list = user_list->next) {
        uuid_user = malloc(sizeof(char) * 37);
        uuid_unparse(((user_t *)user_list->data)->id, uuid_user);
        dprintf(my_team->server.client[i].fd, "619 \"%s\" \"%s\" \"%d\"\n",
                uuid_user, ((user_t *)user_list->data)->username,
                ((user_t *)user_list->data)->status);
    }
}

static void show_team_members(struct my_teams_t *my_team, char **arg, int i)
{
    uuid_t uuid;
    team_t *team = NULL;

    uuid_parse(arg[1], uuid);
    team = find_team_by_uuid(my_team->teams, uuid);
    if (!team) {
        dprintf(my_team->server.client[i].fd, "613 \"%s\"\n", arg[1]);
        return;
    }
    print_all_users(my_team, team, i);
}

int subscribed(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    if (ac == 1)
        show_subscribed_team(my_team, i);
    else if (ac == 2)
        show_team_members(my_team, arg, i);
    else
        return (-1);
    return (0);
}