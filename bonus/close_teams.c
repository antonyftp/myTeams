/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** close_teams
*/

#include "server.h"

void free_messages(message_list_t *list)
{
    message_list_t *prev;

    while (list) {
        free(((message_t *)list->data)->message);
        prev = list;
        list = list->next;
        free(prev);
    }
}

void free_threads(channel_list_t *channels)
{
    thread_list_t *list = ((channel_t *)channels->data)->threads;
    thread_list_t *prev;

    while (list) {
        free_messages(((thread_t *)list->data)->message);
        free(((thread_t *)list->data)->title);
        uuid_clear(((thread_t *)list->data)->id);
        free(((thread_t *)list->data)->original_post);
        prev = list;
        list = list->next;
        free(prev);
    }
}

void free_channel(team_list_t *teams)
{
    channel_list_t *list = ((team_t *)teams->data)->channels;
    channel_list_t *prev;

    while (list) {
        free_threads(list);
        free(((channel_t *)list->data)->title);
        uuid_clear(((channel_t *)list->data)->id);
        free(((channel_t *)list->data)->description);
        prev = list;
        list = list->next;
        free(prev);
    }
}