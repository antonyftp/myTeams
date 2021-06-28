/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** $
*/

#include "client.h"

static void syntax_error_handling(client_t *client, char *command,
    char **splited_commmand)
{
    const char *func_names[12] = { "/logout", "/users", "/user", "/send", \
    "/messages", "/subscribe", "/subscribed", "/unsubscribe", "/use", \
    "/create", "/list", "/info" };
    void (*function[12])(client_t *client, char *command,
    char **splited_commmand) = { &send_logout, &no_arg, &one_arg, &two_arg, \
    &one_arg, &one_arg, &no_or_one_arg, &one_arg, &undefined_arg, \
    &undefined_arg, &undefined_arg, &undefined_arg };

    for (int i = 0; i < 12; ++i)
        if (!strcmp(func_names[i], splited_commmand[0])) {
            function[i](client, command, splited_commmand);
            return;
        }
    printf("Unknown command, use /help if you need help.\n");
}

void send_command(client_t *client, char *command, char **splited_commmand)
{
    if (!splited_commmand)
        return;
    if (!strcmp(splited_commmand[0], "/help")) {
        if (tab_len(splited_commmand) == 1)
            printf("%s", HELP);
        else
            printf(AGRS_NOT_IMPLEMENTED, "/help");
        return;
    } else if (!strcmp(splited_commmand[0], "/login")) {
        if (client->is_loggin == NOT_LOGGEDIN &&
        tab_len(splited_commmand) == 2 && strlen(splited_commmand[1]) <= 32) {
            dprintf(client->socket_fd, "%s\n", command);
        } else if (tab_len(splited_commmand) != 2) {
            printf(AGRS_NOT_IMPLEMENTED, "/login");
        } else
            printf(ALREADY_LOGGEDIN);
        return;
    }
    syntax_error_handling(client, command, splited_commmand);
    free_tab(splited_commmand);
}