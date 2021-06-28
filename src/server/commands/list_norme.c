/*
** EPITECH PROJECT, 2021
** MyTeams
** File description:
** list_norme.c
*/

#include "server.h"

void uuid_parsing(thread_list_t *list, char **id, char **uid)
{
    *id = malloc(37);
    *uid = malloc(37);
    uuid_unparse(((thread_t *)list->data)->id, *id);
    uuid_unparse(((thread_t *)list->data)->owner->id, *uid);
}

void uuid_parsing_reply(char **user_id, message_list_t *list)
{
    *user_id = malloc(37);
    uuid_unparse(((message_t *)list->data)->sender->id, *user_id);
}

void print_error_reply(struct my_teams_t *my_team, int i)
{
    dprintf(my_team->server.client[i].fd, "615\n");
}

char *convert_timestamp(time_t timestamp)
{
    char *buf = malloc(sizeof(char) * 21);

    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
    buf[20] = '\0';
    return (buf);
}