/*
** EPITECH PROJECT, 2021
** MyTeams
** File description:
** logout.cpp
*/

#include "client.h"

void logout(char **args, client_t *client)
{
    client->quit = QUIT;
}