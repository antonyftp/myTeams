/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

void load_cache(struct my_teams_t *my_team)
{
    user_list_t *users = load_users();
    thread_list_t *thread = load_thread(users);
    channel_list_t *channel = load_channel(thread);
    team_list_t *team = load_teams(users, channel);
    private_message_list_t *message = load_privatemessages(users);
    my_team->users = users;
    my_team->teams = team;
    my_team->private_message = message;
}

void reset_client(struct my_teams_t *my_team, int i)
{
    my_team->server.client[i].fd = -1;
    my_team->server.client[i].user = NULL;
    my_team->server.client[i].use_status = Nothing;
    my_team->server.client[i].connected = false;
}

void init_server(struct my_teams_t *my_team)
{
    int opt = 1;
    for (int i = 0; i < CLIENT_MAX; i++)
        my_team->server.client[i].fd = -1;
    MAIN_SOCKET = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(MAIN_SOCKET,
        SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    my_team->server.my_socket.sin_family = AF_INET;
    my_team->server.my_socket.sin_port = htons(my_team->server.port);
    my_team->server.my_socket.sin_addr.s_addr = INADDR_ANY;
    bind(MAIN_SOCKET, (struct sockaddr *)&my_team->server.my_socket,
        sizeof(my_team->server.my_socket));
    listen(MAIN_SOCKET, 10);
    my_team->server.client_size = sizeof(struct sockaddr_in);
    load_cache(my_team);
    for (int i = 0; i < 50; ++i)
        reset_client(my_team, i);
}

int main(int ac, char **av)
{
    struct my_teams_t my_team;

    if (ac != 2)
        return (84);
    if (check_port(av[1]) != 0)
        return (84);
    my_team.server.port = atoi(av[1]);
    init_server(&my_team);
    server_loop(&my_team);
    close(my_team.server.sockets.main_socket);
    return (0);
}