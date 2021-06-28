/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** list_error
*/

#include "server.h"

int check_team(struct my_teams_t *my_team, int i)
{
    if (find_team_by_uuid(my_team->teams,
        my_team->server.client[i].team_uuid) == NULL)
        return (-1);
    return (0);
}

int check_channel(struct my_teams_t *my_team, int i)
{
    if (check_team(my_team, i) == -1)
        return (-1);
    if (find_channel_by_uuid(find_team_by_uuid(my_team->teams,
        my_team->server.client[i].team_uuid)->channels,
        my_team->server.client[i].channel_uuid) == NULL)
        return (-1);
    return (0);
}

int check_thread(struct my_teams_t *my_team, int i)
{
    if (check_channel(my_team, i) == -1)
        return (-1);
    if (find_thread_by_uuid(find_channel_by_uuid(
        find_team_by_uuid(my_team->teams,
        my_team->server.client[i].team_uuid)->channels,
        my_team->server.client[i].channel_uuid)->threads,
        my_team->server.client[i].thread_uuid) == NULL)
        return (-1);
    return (0);
}