/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

static int team(struct my_teams_t *my_team, int i, char **arg)
{
    uuid_t uuid;

    uuid_parse(arg[1], my_team->server.client[i].team_uuid);
    return (0);
}

static int channel(struct my_teams_t *my_team, int i, char **arg)
{
    uuid_t uuid;

    uuid_parse(arg[1], my_team->server.client[i].team_uuid);
    uuid_parse(arg[2], my_team->server.client[i].channel_uuid);
    return (0);
}

static int thread(struct my_teams_t *my_team, int i, char **arg)
{
    uuid_t uuid;

    uuid_parse(arg[1], my_team->server.client[i].team_uuid);
    uuid_parse(arg[2], my_team->server.client[i].channel_uuid);
    uuid_parse(arg[3], my_team->server.client[i].thread_uuid);
    return (0);
}

static int find(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    switch (ac) {
        case 1:
            my_team->server.client[i].use_status = Nothing;
            break;
        case 2:
            team(my_team, i, arg);
            my_team->server.client[i].use_status = Team;
            break;
        case 3:
            channel(my_team, i, arg);
            my_team->server.client[i].use_status = Channel;
            break;
        case 4:
            thread(my_team, i, arg);
            my_team->server.client[i].use_status = Thread;
            break;
        default:
            return (-1);
    }
    return (0);
}

int use(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    for (int index = 1; index < ac; ++index)
        if (!is_uuid(arg[index]))
            return (-1);
    return (find(my_team, arg, i, ac));
}