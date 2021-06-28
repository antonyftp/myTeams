/*
** EPITECH PROJECT, 2024
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** Created by antonyftp
*/
#include "client.h"

static int helper(void)
{
    printf(HELPER);

    return (0);
}

int main(int argc, char **argv)
{
    if (argc == 2 && !strcmp(argv[1], "-help"))
        return (helper());
    else if (argc != 3 || (argc == 3 && !is_number(argv[2]))) {
        printf(INVALID_ARGS);
        return (84);
    }
    if (client(argv[1], atoi(argv[2]))) {
        printf(SHOULD_TRY_AGAIN);
        return (84);
    }

    return (0);
}