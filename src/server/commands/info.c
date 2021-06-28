/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

void info_user(struct my_teams_t *my_team, int i)
{
    user_t *client = my_team->server.client[i].user;
    char id[37];

    uuid_unparse(client->id, id);
    dprintf(my_team->server.client[i].fd, "619 %s %s %d\n", id,
        client->username,
        my_team->server.client[i].connected);
}

void info_team(struct my_teams_t *my_team, int i)
{
    team_t *data = find_team_by_uuid(my_team->teams,
        my_team->server.client[i].team_uuid);
    char id[37];

    if (check_team(my_team, i) == -1) {
        dprintf(my_team->server.client[i].fd, "613\n");
        return;
    }
    uuid_unparse(data->id, id);
    dprintf(my_team->server.client[i].fd, "620 %s %s %s\n", id, data->title,
        data->description);
}

void info_channel(struct my_teams_t *my_team, int i)
{
    channel_t *data = find_channel_by_uuid(find_team_by_uuid(my_team->teams,
        my_team->server.client[i].team_uuid)->channels,
        my_team->server.client[i].channel_uuid);
    char id[37];

    if (check_team(my_team, i) == -1) {
        dprintf(my_team->server.client[i].fd, "613\n");
        return;
    }
    if (check_channel(my_team, i) == -1) {
        dprintf(my_team->server.client[i].fd, "614\n");
        return;
    }
    uuid_unparse(data->id, id);
    dprintf(my_team->server.client[i].fd, "621 %s %s %s\n", id, data->title,
        data->description);
}

void info_thread(struct my_teams_t *my_team, int i)
{
    thread_t *data = find_thread_by_uuid(find_channel_by_uuid(
        find_team_by_uuid(my_team->teams,
        my_team->server.client[i].team_uuid)->channels,
        my_team->server.client[i].channel_uuid)->threads,
        my_team->server.client[i].thread_uuid);
    char id[37];
    char user_id[37];

    if (check_thread(my_team, i) == -1) {
        dprintf(my_team->server.client[i].fd, "615\n");
        return;
    }
    uuid_unparse(data->id, id);
    uuid_unparse(my_team->server.client[i].user->id, user_id);
    dprintf(my_team->server.client[i].fd, "622 %s %s %ld %s %s\n", id, user_id,
        data->timestamp, data->title, data->original_post);
}

int info(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    switch (my_team->server.client[i].use_status) {
        case Nothing:
            info_user(my_team, i);
            break;
        case Team:
            info_team(my_team, i);
            break;
        case Channel:
            info_channel(my_team, i);
            break;
        case Thread:
            info_thread(my_team, i);
            break;
    }
    return (0);
}