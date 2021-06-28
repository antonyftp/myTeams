/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** char_to_time.c
*/

#include "client.h"

time_t char_to_time(char *str)
{
    struct tm time = { 0 };

    strptime(str, "%Y-%m-%d %H:%M:%S", &time);
    return (mktime(&time));
}