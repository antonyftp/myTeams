/*
** EPITECH PROJECT, 2021
** MyTeams
** File description:
** print_new_channel.c
*/

#include "server.h"

void print_new_channel(struct my_teams_t *my_team, team_t *team, char **arg,
    int i)
{
    struct client_t *clients = my_team->server.client;
    char *uuid = malloc(sizeof(char) * 37);

    uuid_unparse(find_channel_by_title(team->channels, arg[1])->id, uuid);
    for (int index = 0; index < 50; ++index) {
        if (IS_GOOD_CLIENT)
            dprintf(my_team->server.client[index].fd,
                    "605 \"%s\" \"%s\" \"%s\"\n", uuid, arg[1], arg[2]);
    }
    dprintf(my_team->server.client[i].fd, "624 \"%s\" \"%s\" \"%s\"\n", uuid,
            arg[1], arg[2]);
    free(uuid);
}

static void free_uuid(char *uuid_user, char *uuid_thread, char *uuid_team)
{
    free(uuid_user);
    free(uuid_thread);
    free(uuid_team);
}

void print_reply(struct my_teams_t *my_team, int i, message_t *message_struct)
{
    char *uuid_team = malloc(sizeof(char) * 37);
    char *uuid_thread = malloc(sizeof(char) * 37);
    char *uuid_user = malloc(sizeof(char) * 37);
    team_t *team = find_team_by_uuid(my_team->teams, CLIENT.team_uuid);
    struct client_t *clients = my_team->server.client;
    char timestamp[21];

    uuid_unparse(my_team->server.client[i].team_uuid, uuid_team);
    uuid_unparse(my_team->server.client[i].thread_uuid, uuid_thread);
    uuid_unparse(my_team->server.client[i].user->id, uuid_user);
    for (int index = 0; index < 50; ++index)
        if (IS_GOOD_CLIENT)
            dprintf(CLIENT.fd, "603 \"%s\" \"%s\" \"%s\" \"%s\"\n", uuid_team,
                uuid_thread, uuid_user, message_struct->message);
    strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S",
        localtime(&message_struct->timestamp));
    timestamp[20] = '\0';
    dprintf(CLIENT.fd, "626 \"%s\" \"%s\" \"%s\" \"%s\"\n", uuid_thread,
        uuid_user, timestamp, message_struct->message);
    free_uuid(uuid_user, uuid_thread, uuid_team);
}