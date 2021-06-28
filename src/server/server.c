/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** server
*/

#include "../../includes/server.h"

void add_new(struct my_teams_t *my_team)
{
    if (FD_ISSET(MAIN_SOCKET, &READFDS)) {
        RCV_SOCKET = accept(MAIN_SOCKET, (struct sockaddr *)
            &my_team->server.my_socket, &my_team->server.client_size);
        for (int i = 0; i < CLIENT_MAX; i++) {
            if (my_team->server.client[i].fd == -1) {
                init_client(&my_team->server.client[i], RCV_SOCKET);
                break;
            }
        }
    }
}

void set_server(struct my_teams_t *my_team)
{
    FD_ZERO(&READFDS);
    FD_ZERO(&WRITEFDS);
    FD_SET(STDIN_FILENO, &READFDS);
    FD_SET(MAIN_SOCKET, &READFDS);
    MAXSD = MAIN_SOCKET;

    for (int i = 0; i < CLIENT_MAX; i++) {
        my_team->server.socket_descriptor.sd = my_team->server.client[i].fd;
        if (my_team->server.client[i].fd > 0) {
            FD_SET(my_team->server.client[i].fd, &READFDS);
            FD_SET(my_team->server.client[i].fd, &WRITEFDS);
        }
        if (my_team->server.client[i].fd > MAXSD)
            MAXSD = my_team->server.socket_descriptor.sd;
    }
}

void server_loop(struct my_teams_t *my_team)
{
    struct timeval timer;

    while (1) {
        timer.tv_sec = 2;
        timer.tv_usec = 0;
        set_server(my_team);
        select(my_team->server.socket_descriptor.max_sd + 1, &READFDS,
            &WRITEFDS, NULL, &timer);
        add_new(my_team);
        main_command(my_team);
    }
}