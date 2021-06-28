/*
** EPITECH PROJECT, 2021
** MyTeams
** File description:
** create_channel.c
*/

#include "server.h"

int unautorized(struct my_teams_t *my_team, int i)
{
    if (find_user_by_uuid(find_team_by_uuid(my_team->teams,
        CLIENT.team_uuid)->users, CLIENT.user->id) != NULL)
        return (0);
    return (1);
}

static void send_error(struct my_teams_t *my_team, int i)
{
    dprintf(my_team->server.client[i].fd, "613\n");
}

static void set_channel(channel_t *channel, char **arg, team_t *team)
{
    channel->threads = NULL;
    channel->title = strdup(arg[1]);
    channel->description = strdup(arg[2]);
    uuid_generate(channel->id);
    team->channels = add_node(team->channels, channel);
}

void create_new_channel(struct my_teams_t *my_team, int i, char **arg)
{
    channel_t *channel = malloc(sizeof(channel_t));
    team_t *team = NULL;
    char *uuid = malloc(sizeof(char) * 37);
    char *uuid_team = malloc(sizeof(char) * 37);

    if (check_team(my_team, i) == -1)
        return (send_error(my_team, i));
    team = find_team_by_uuid(my_team->teams,
        my_team->server.client[i].team_uuid);
    if (strlen(arg[2]) > 255 || unautorized(my_team, i))
        return;
    set_channel(channel, arg, team);
    uuid_unparse(channel->id, uuid);
    uuid_unparse(team->id, uuid_team);
    print_new_channel(my_team, team, arg, i);
    server_event_channel_created(uuid_team, uuid, channel->title);
    add_channel(channel->title, channel->id, channel->description);
    set_channel_parent(team->id, channel->id);
    free(uuid);
}