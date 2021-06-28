/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** channel_list
*/

#include "../includes/server.h"

struct channel_t *add_channelnode(struct channel_t *node,
    struct channel_t *list)
{
    struct channel_t *temp_first = list;

    if (!list) {
        list = node;
        return (list);
    }
    while (list->next)
        list = list->next;
    list->next = node;
    list = temp_first;
    return (list);
}
struct channel_t *remove_channelnode(uuid_t searched, struct channel_t *list)
{
    struct channel_t *temp_first = list;
    struct channel_t *before = NULL;

    while (list && list->id != searched) {
        before = list;
        list = list->next;
    }
    if (list == NULL) {
        list = temp_first;
        return (NULL);
    }
    if (list == temp_first) {
        list = list->next;
        list = temp_first;
        return (list);
    }
    before->next = list->next;
    list = temp_first;
    return (list);
}

struct channel_t *find_channelnode(uuid_t searched, struct channel_t *list)
{
    struct channel_t *temp = list;

    while (temp && temp->id != searched) {
        temp = temp->next;
    }
    return (temp);
}