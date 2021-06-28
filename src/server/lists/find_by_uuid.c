/*
** EPITECH PROJECT, 2021
** Project
** File description:
** find_by_uuid.c
*/

#include "../../includes/linked_list.h"

user_t *find_user_by_uuid(user_list_t *list_head, uuid_t uuid)
{
    user_list_t *tmp = list_head;

    if (!tmp)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (!uuid_compare(uuid, ((user_t *)tmp->data)->id))
            return ((user_t *)tmp->data);
    }
    return (NULL);
}

thread_t *find_thread_by_uuid(thread_list_t *list_head, uuid_t uuid)
{
    thread_list_t *tmp = list_head;

    if (!tmp)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (!uuid_compare(uuid, ((thread_t *)tmp->data)->id))
            return ((thread_t *)tmp->data);
    }
    return (NULL);
}

channel_t *find_channel_by_uuid(channel_list_t *list_head, uuid_t uuid)
{
    channel_list_t *tmp = list_head;

    if (!tmp)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (!uuid_compare(uuid, ((channel_t *)tmp->data)->id))
            return ((channel_t *)tmp->data);
    }
    return (NULL);
}

team_t *find_team_by_uuid(team_list_t *list_head, uuid_t uuid)
{
    team_list_t *tmp = list_head;

    if (!tmp)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (!uuid_compare(uuid, ((team_t *)tmp->data)->id))
            return ((team_t *)tmp->data);
    }
    return (NULL);
}