/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

void list_team(struct my_teams_t *my_team, int i)
{
    team_list_t *list = my_team->teams;
    char *id;

    while (list != NULL) {
        id = malloc(37);
        uuid_unparse(((team_t *)list->data)->id, id);
        dprintf(my_team->server.client[i].fd, "608 \"%s\" \"%s\" \"%s\"\n", id,
            ((team_t *)list->data)->title, ((team_t *)list->data)->description);
        free(id);
        list = list->next;
    }
}

void list_channel(struct my_teams_t *my_team, int i)
{
    team_t *team = find_team_by_uuid(my_team->teams,
        my_team->server.client[i].team_uuid);
    channel_list_t *list;
    char *id;

    if (check_team(my_team, i) == -1) {
        dprintf(my_team->server.client[i].fd, "613\n");
        return;
    }
    list = team->channels;
    while (list != NULL) {
        id = malloc(37);
        uuid_unparse(((channel_t *)list->data)->id, id);
        dprintf(my_team->server.client[i].fd, "609 \"%s\" \"%s\" \"%s\"\n", id,
            ((channel_t *)list->data)->title,
            ((channel_t *)list->data)->description);
        free(id);
        list = list->next;
    }
}

void list_thread(struct my_teams_t *my_team, int i)
{
    channel_t *channels = find_channel_by_uuid(find_team_by_uuid(my_team->teams,
        CLIENT.team_uuid)->channels, CLIENT.channel_uuid);
    thread_list_t *list;
    char *id;
    char *uid;

    if (check_channel(my_team, i) == -1) {
        dprintf(my_team->server.client[i].fd, "614\n");
        return;
    }
    list = channels->threads;
    for (; list != NULL; list = list->next) {
        uuid_parsing(list, &id, &uid);
        dprintf(CLIENT.fd, "610 \"%s\" \"%s\" \"%ld\" \"%s\" \"%s\"\n", id, uid,
        ((thread_t *)list->data)->timestamp, ((thread_t *)list->data)->title,
        ((thread_t *)list->data)->original_post);
        free(id);
        free(uid);
    }
}

void list_reply(struct my_teams_t *my_team, int i)
{
    thread_t *thread = NULL;
    message_list_t *list;
    char *id = malloc(37);
    char *user_id = malloc(sizeof(char) * 37);

    if (check_thread(my_team, i) == -1)
        return (print_error_reply(my_team, i));
    thread = FIND_THREAD;
    list = thread->message;
    uuid_unparse(thread->id, id);
    uuid_unparse(thread->owner->id, user_id);
    dprintf(CLIENT.fd,  "611 \"%s\" \"%s\" \"%s\" \"%s\"\n", id, user_id, \
        convert_timestamp(thread->timestamp), thread->original_post);
    for (; list != NULL; list = list->next) {
        uuid_parsing_reply(&user_id, list);
        SEND_SOCKET_REPLY;
        free(user_id);
    }
    free(id);
}

int list(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    switch (my_team->server.client[i].use_status) {
        case Nothing:
            list_team(my_team, i);
            break;
        case Team:
            list_channel(my_team, i);
            break;
        case Channel:
            list_thread(my_team, i);
            break;
        case Thread:
            list_reply(my_team, i);
            break;
    }
    return (0);
}