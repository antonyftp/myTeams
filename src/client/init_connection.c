/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** init_connection
*/

#include "client.h"

int init_connection(char *ip, int port)
{
    int socket_fd = 0;
    struct sockaddr_in serv_in;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        printf(ERROR_CREATE_SOCKET);
        return (-1);
    }
    serv_in.sin_addr.s_addr = inet_addr(ip);
    serv_in.sin_port = htons(port);
    serv_in.sin_family = AF_INET;
    if (connect(socket_fd, (struct sockaddr *)&serv_in,
        sizeof(serv_in)) == -1) {
        printf(ERROR_CONNECT_SERVER);
        return (-1);
    }
    return (socket_fd);
}