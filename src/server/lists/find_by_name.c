/*
** EPITECH PROJECT, 2021
** Project
** File description:
** find_by_name.c
*/

#include "../../includes/linked_list.h"

user_t *find_user_by_name(user_list_t *list_head, char *name)
{
    user_list_t *tmp = list_head;

    if (!tmp)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (!strcmp(name, ((user_t *)tmp->data)->username))
            return ((user_t *)tmp->data);
    }
    return (NULL);
}

thread_t *find_thread_by_title(thread_list_t *list_head, char *title)
{
    thread_list_t *tmp = list_head;

    if (!tmp)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (!strcmp(title, ((thread_t *)tmp->data)->title))
            return ((thread_t *)tmp->data);
    }
    return (NULL);
}

channel_t *find_channel_by_title(channel_list_t *list_head, char *title)
{
    channel_list_t *tmp = list_head;

    if (!tmp)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (!strcmp(title, ((channel_t *)tmp->data)->title))
            return ((channel_t *)tmp->data);
    }
    return (NULL);
}

team_t *find_team_by_title(team_list_t *list_head, char *title)
{
    team_list_t *tmp = list_head;

    if (!tmp)
        return (NULL);
    for (; tmp; tmp = tmp->next) {
        if (!strcmp(title, ((team_t *)tmp->data)->title))
            return ((team_t *)tmp->data);
    }
    return (NULL);
}