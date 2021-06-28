/*
** EPITECH PROJECT, 2021
** MyTeams
** File description:
** create_thread.c
*/

#include "server.h"

static void free_print(char *uuid, char *uuid_user)
{
    free(uuid);
    free(uuid_user);
}

static void print_thread(struct my_teams_t *my_team, thread_t *thread, int i)
{
    char *uuid = malloc(sizeof(char) * 37);
    char *uuid_user = malloc(sizeof(char) * 37);
    char buf[21];
    team_t *team = find_team_by_uuid(my_team->teams, CLIENT.team_uuid);
    struct client_t *clients = my_team->server.client;

    uuid_unparse(thread->id, uuid);
    uuid_unparse(thread->owner->id, uuid_user);
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", localtime(&thread->timestamp));
    buf[20] = '\0';
    for (int index = 0; index < 50; ++index) {
        if (IS_GOOD_CLIENT)
            dprintf(my_team->server.client[index].fd,
                "606 \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",
                uuid, uuid_user, buf, thread->title, thread->original_post);
    }
    dprintf(CLIENT.fd, "625  \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",
        uuid, uuid_user, buf, thread->title, thread->original_post);
    free_print(uuid, uuid_user);
}

static void print_new_thread(struct my_teams_t *my_team, int i,
        thread_t *thread, channel_t *channel)
{
    char *uuid = malloc(sizeof(char) * 37);
    char *uuid_user = malloc(sizeof(char) * 37);
    char *uuid_channel = malloc(sizeof(char) * 37);
    char buf[21];

    uuid_unparse(thread->id, uuid);
    uuid_unparse(thread->owner->id, uuid_user);
    uuid_unparse(channel->id, uuid_channel);
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", localtime(&thread->timestamp));
    buf[20] = '\0';
    print_thread(my_team, thread, i);
    add_thread(thread->title, thread->id, thread->owner->username,
        thread->original_post);
    set_thread_parent(channel->id, thread->id);
    server_event_thread_created(uuid_channel, uuid, uuid_user, thread->title,
                                thread->original_post);
    free(uuid);
    free(uuid_user);
    free(uuid_channel);
}

void create_new_thread(struct my_teams_t *my_team, int i, char **arg)
{
    thread_t *thread = malloc(sizeof(thread_t));
    channel_t *channel = NULL;

    if (check_channel(my_team, i) == -1) {
        dprintf(my_team->server.client[i].fd, "613\n");
        return;
    }
    if (strlen(arg[2]) > 512 || unautorized(my_team, i))
        return;
    channel = find_channel_by_uuid(find_team_by_uuid(my_team->teams,
        my_team->server.client[i].team_uuid)->channels,
        my_team->server.client[i].channel_uuid);
    thread->title = strdup(arg[1]);
    thread->original_post = strdup(arg[2]);
    thread->message = NULL;
    uuid_generate(thread->id);
    thread->owner = my_team->server.client[i].user;
    thread->timestamp = time(NULL);
    channel->threads = add_node(channel->threads, thread);
    print_new_thread(my_team, i, thread, channel);
}