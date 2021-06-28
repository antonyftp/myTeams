/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** get_line
*/

#include "client.h"

char *get_line(int fd)
{
    char *buf = malloc(sizeof(char) * 256);
    char read_char = 0;
    size_t ret_val = 1;

    if (!buf)
            return (NULL);
    for (int i = 0; read_char != '\n';) {
        ret_val = read(fd, &read_char, 1);
        if (ret_val == 1) {
            buf[i++] = read_char;
        } else if (ret_val == -1)
            return ((char *)-1);
        if (read_char == '\n')
            buf[i - 1] = '\0';
    }

    return (buf);
}