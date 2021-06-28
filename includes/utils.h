/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** Created by antonyftp
*/

#ifndef MYTEAMS_UTILS_H
#define MYTEAMS_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#define KEY "68768767546534765356-myteams"

char **split_string(char *str, char *tok);
void free_tab(char **tab);
int tab_len(char **tab);
FILE *open_file(char *filepath, char *mode);
int check_file(char *filepath);

#endif //MYTEAMS_UTILS_H
