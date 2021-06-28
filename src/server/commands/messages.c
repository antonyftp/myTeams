/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

static void find_message(private_message_t **private_message,
    struct my_teams_t *my_team, uuid_t uuid, int i)
{
    *private_message = find_private_message(my_team->private_message,
        my_team->server.client[i].user->id, uuid);
}

static int free_uuid(char *uuid_str)
{
    free(uuid_str);
    return (0);
}

int messages(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    private_message_t *private_message = NULL;
    message_list_t *message_list = NULL;
    uuid_t uuid;
    char *uuid_str = malloc(37);
    char timestamp[21];

    uuid_parse(arg[1], uuid);
    find_message(&private_message, my_team, uuid, i);
    if (private_message == NULL)
        return (-1);
    message_list = private_message->message_list;
    for (; message_list != NULL; message_list = message_list->next) {
        uuid_unparse(((message_t *)message_list->data)->sender->id, uuid_str);
        strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S",
            localtime(&((message_t *)message_list->data)->timestamp));
        timestamp[20] = '\0';
        dprintf(my_team->server.client[i].fd, "612 \"%s\" \"%s\" \"%s\"\n",
            uuid_str, timestamp, ((message_t *)message_list->data)->message);
    }
    return (free_uuid(uuid_str));
}