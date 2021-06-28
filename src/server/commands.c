/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

static commands_t commands[] = {
    {"/create", &create},
    {"/info", &info},
    {"/list", &list},
    {"/login", &login},
    {"/logout", &logout},
    {"/messages", &messages},
    {"/send", &send_message},
    {"/subscribe", &subscribe},
    {"/subscribed", &subscribed},
    {"/unsubscribe", &unsubscribed},
    {"/use", &use},
    {"/user", &user},
    {"/users", &users},
    {NULL, NULL} };

static int cmp_command(const char *cmd, const char *text)
{
    int	i = 0;
    int	j = 0;

    while (cmd && text && cmd[i] && text[j] && cmd[i] == text[j]) {
        i += 1;
        j += 1;
    }
    if (cmd && cmd[i] == '\0')
        return (1);
    return (0);
}

static int dispatch_command(struct my_teams_t *my_team, char **av, int x,
    int ac)
{
    for (int i = 0; av[0] && CMD_PTR; ++i)
        if (!strcmp(av[0], commands[i].cmd))
            return (commands[i].func_ptr(my_team, av, x, ac));
    return (0);
}

int get_args(char *ptr, char **argv, int max)
{
    int i = 0;
    char *origin;

    while (*ptr && i < max) {
        while (IS_SPACE(*ptr))
            ptr++;
        if (*ptr) {
            origin = ptr;
            while (*ptr && !IS_SPACE(*ptr))
                ptr++;
            if (*ptr)
                *ptr++ = 0;
            argv[i++] = origin;
        }
    }
    return (i);
}

void main_command(struct my_teams_t *my_team)
{
    int ac;
    size_t len;
    char *av[50];
    char buffer[1024];
    char **args = NULL;

    if (FD_ISSET(STDIN_FILENO, &READFDS))
        do_server_command(my_team);
    for (int i = 0; i < CLIENT_MAX; i++) {
        SD = my_team->server.client[i].fd;
        if (FD_ISSET(SD, &READFDS)) {
            bzero(buffer, 1024);
            len = read(SD, buffer, 1024);
            --len;
            buffer[len] = 0;
            args = split_args(buffer);
            dispatch_command(my_team, args, i, tab_len(args));
        }
    }
}