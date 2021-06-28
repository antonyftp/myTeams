/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** server_command
*/

#include "server.h"

static void find_command(struct my_teams_t *my_team, char *buffer)
{
    char *argv[] = {"/bin/rm", "-rf", "./savefiles", 0};
    char *envp[] = {NULL};

    if (strcmp(buffer, "/disconnectAll") == 0)
        disconnect(my_team);
    if (strcmp(buffer, "/close") == 0) {
        disconnect(my_team);
        close_server(my_team);
        exit(0);
    }
    if (strcmp(buffer, "/clear_close") == 0) {
        disconnect(my_team);
        execve("/bin/rm", argv, envp);
        close_server(my_team);
        exit(0);
    }
}

void do_server_command(struct my_teams_t *my_team)
{
    char buffer[1024];
    size_t len;

    bzero(buffer, 1024);
    len = read(STDIN_FILENO, buffer, 1024);
    --len;
    buffer[len] = 0;
    find_command(my_team, buffer);
}