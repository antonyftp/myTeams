/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** close
*/

#include "server.h"

static void free_team(struct my_teams_t *my_team)
{
    team_list_t *list = my_team->teams;
    team_list_t *prev;

    while (list) {
        free_channel(list);
        free(((team_t *)list->data)->title);
        uuid_clear(((team_t *)list->data)->id);
        free(((team_t *)list->data)->description);
        prev = list;
        list = list->next;
        free(prev);
    }
}

static void free_private(struct my_teams_t *my_team)
{
    private_message_list_t *list_priv = my_team->private_message;
    private_message_list_t *prev_priv;

    while (list_priv) {
        free_messages(((private_message_t *)list_priv->data)->message_list);
        prev_priv = list_priv;
        list_priv = list_priv->next;
        free(prev_priv);
    }
}

static void free_users(struct my_teams_t *my_team)
{
    user_list_t *list = my_team->users;
    user_list_t *prev;

    while (list) {
        free(((user_t *)list->data)->username);
        uuid_clear(((user_t *)list->data)->id);
        prev = list;
        list = list->next;
        free(prev);
    }
}

void close_server(struct my_teams_t *my_team)
{
    free_team(my_team);
    free_private(my_team);
    free_users(my_team);
}