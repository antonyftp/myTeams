/*
** EPITECH PROJECT, 2021
** Parser
** File description:
** load_clients.c
*/

#include "loader.h"

static user_t *set_user_infos(char **splited_line)
{
    user_t *user_infos = malloc(sizeof(user_t));

    user_infos->username = strdup(splited_line[0]);
    user_infos->status = 0;
    uuid_parse(splited_line[1], user_infos->id);
    server_event_user_loaded(splited_line[1], splited_line[0]);

    return (user_infos);
}

static user_list_t *free_users(char *line, FILE *file, user_list_t *users)
{
    free(line);
    fclose(file);
    return (users);
}

user_list_t *load_users(void)
{
    user_list_t *users_list_head = NULL;
    FILE *file = open_file(USERS_FILEPATH, "r");
    size_t size = 0;
    struct stat st = {0};
    char *line = NULL;
    char **splitted_line = NULL;

    if (stat("savefiles", &st) == -1)
        mkdir("savefiles", 0700);
    if (file == (FILE *)-1)
        return (create_file(USERS_FILEPATH));
    getline(&line, &size, file);
    while (getline(&line, &size, file) != -1) {
        splitted_line = split_string(line, ";\n");
        users_list_head = add_node(users_list_head,
            set_user_infos(splitted_line));
        free_tab(splitted_line);
    }
    return (free_users(line, file, users_list_head));
}