/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** send_command_error_handling
*/

#include "client.h"

void no_arg(client_t *client, char *command, char **splited_commmand)
{
    if (tab_len(splited_commmand) == 1) {
        if (client->is_loggin != LOGGEDIN)
            printf(MUST_BE_LOGGED);
        else
            dprintf(client->socket_fd, "%s\n", command);
        return;
    }
    printf(AGRS_NOT_IMPLEMENTED, splited_commmand[0]);
}

void one_arg(client_t *client, char *command, char **splited_commmand)
{
    if (tab_len(splited_commmand) == 2) {
        if (client->is_loggin != LOGGEDIN)
            printf(MUST_BE_LOGGED);
        else
            dprintf(client->socket_fd, "%s\n", command);
        return;
    }
    printf(AGRS_NOT_IMPLEMENTED, splited_commmand[0]);
}

void two_arg(client_t *client, char *command, char **splited_commmand)
{
    if (tab_len(splited_commmand) == 3) {
        if (client->is_loggin != LOGGEDIN)
            printf(MUST_BE_LOGGED);
        else
            dprintf(client->socket_fd, "%s\n", command);
        return;
    }
    printf(AGRS_NOT_IMPLEMENTED, splited_commmand[0]);
}

void no_or_one_arg(client_t *client, char *command, char **splited_commmand)
{
    if (tab_len(splited_commmand) == 1 || tab_len(splited_commmand) == 2) {
        if (client->is_loggin != LOGGEDIN)
            printf(MUST_BE_LOGGED);
        else
            dprintf(client->socket_fd, "%s\n", command);
        return;
    }
    printf(AGRS_NOT_IMPLEMENTED, splited_commmand[0]);
}

void undefined_arg(client_t *client, char *command, char **splited_commmand)
{
    if (client->is_loggin != LOGGEDIN)
        printf(MUST_BE_LOGGED);
    else
        dprintf(client->socket_fd, "%s\n", command);
}