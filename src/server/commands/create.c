/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

void init_team(team_t *team, char **arg, int i, struct my_teams_t *my_team)
{
    team->channels = NULL;
    team->description = strdup(arg[2]);
    team->title = strdup(arg[1]);
    uuid_generate(team->id);
    team->users = NULL;
    team->owner = CLIENT.user;
    my_team->teams = add_node(my_team->teams, team);
}

static void create_new_team(struct my_teams_t *my_team, int i, char **arg)
{
    team_t *team = malloc(sizeof(team_t));
    char *uuid = malloc(sizeof(char) * 37);
    char *uuid_user = malloc(sizeof(char) * 37);

    if (strlen(arg[2]) > 255)
        return;
    init_team(team, arg, i, my_team);
    uuid_unparse(team->id, uuid);
    uuid_unparse(my_team->server.client[i].user->id, uuid_user);
    for (int j = 0; j < 50; ++j)
        if (CLIENT_J.connected && CLIENT_J.user && i != j)
            dprintf(CLIENT_J.fd, "604 \"%s\" \"%s\" \"%s\"\n",
                    uuid, arg[1], arg[2]);
    dprintf(CLIENT.fd, "623 \"%s\" \"%s\" \"%s\"\n", uuid, arg[1], arg[2]);
    add_team(team->title, team->id, team->description, team->owner->username);
    server_event_team_created(uuid, team->title, uuid_user);
    free(uuid);
}

static void print_new_reply(struct my_teams_t *my_team, int i, thread_t *thread,
        message_t *message_struct)
{
    char *uuid_team = malloc(sizeof(char) * 37);
    char *uuid_thread = malloc(sizeof(char) * 37);
    char *uuid_user = malloc(sizeof(char) * 37);

    uuid_unparse(my_team->server.client[i].team_uuid, uuid_team);
    uuid_unparse(my_team->server.client[i].thread_uuid, uuid_thread);
    uuid_unparse(my_team->server.client[i].user->id, uuid_user);
    print_reply(my_team, i, message_struct);
    add_thread_answer(thread->id, message_struct->sender->username,
        message_struct->message, message_struct->timestamp);
    server_event_reply_created(uuid_thread, uuid_user, message_struct->message);
    free(uuid_user);
    free(uuid_thread);
    free(uuid_team);
}

static void create_new_reply(char *message, struct my_teams_t *my_team, int i)
{
    message_t *message_struct = malloc(sizeof(message_t));
    thread_t *thread = NULL;

    if (check_thread(my_team, i) == -1) {
        dprintf(my_team->server.client[i].fd, "613\n");
        return;
    }
    if (strlen(message) > 512 || unautorized(my_team, i))
        return;
    thread = find_thread_by_uuid(find_channel_by_uuid(
            find_team_by_uuid(my_team->teams,
            my_team->server.client[i].team_uuid)->channels,
            my_team->server.client[i].channel_uuid)->threads,
            my_team->server.client[i].thread_uuid);
    message_struct->message = strdup(message);
    message_struct->sender = my_team->server.client[i].user;
    message_struct->timestamp = time(NULL);
    thread->message = add_node(thread->message, message_struct);
    print_new_reply(my_team, i, thread, message_struct);
}

int create(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    if (my_team->server.client[i].use_status == Thread) {
        if (ac != 2)
            return (-1);
    } else if (ac != 3)
        return (-1);
    switch (my_team->server.client[i].use_status) {
        case Nothing:
            create_new_team(my_team, i, arg);
            break;
        case Team:
            create_new_channel(my_team, i, arg);
            break;
        case Channel:
            create_new_thread(my_team, i, arg);
            break;
        case Thread:
            create_new_reply(arg[1], my_team, i);
            break;
    }
    return (0);
}