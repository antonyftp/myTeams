/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** loader.h
*/

#ifndef PARSER_USER_H
#define PARSER_USER_H

#define _XOPEN_SOURCE 700

#include <sys/stat.h>
#include "utils.h"
#include "linked_list.h"
#include "logging_server.h"

#define USERS_FILEPATH  "savefiles/users.cache"
#define TEAMS_FILEPATH "savefiles/teams.cache"
#define THREADS_FILEPATH "savefiles/threads.cache"
#define CHANNELS_FILEPATH "savefiles/channels.cache"
#define PRIVATEMESSAGES_FILEPATH "savefiles/privatemessages.cache"

/**
* @brief Must be called when initializing the server in order to load saved
* users
* @return A linked list which contain all saved users
*/
user_list_t *load_users(void);

/**
* @brief Must be called when initializing the server in order to load saved
* teams
* @return A linked list which contain all saved teams
*/
team_list_t *load_teams(user_list_t *users, channel_list_t *channels);

/**
* @brief Must be called when initializing the server in order to load saved
* threads
* @return A linked list which contain all saved threads
*/
thread_list_t *load_thread(user_list_t *users);

/**
* @brief Must be called when initializing the server in order to load saved
* channels
* @return A linked list which contain all saved channels
*/
channel_list_t *load_channel(thread_list_t *thread);

/**
* @brief Must be called when initializing the server in order to load saved
* channels
* @return A linked list which contain all saved private messages
*/
private_message_list_t *load_privatemessages(user_list_t *users);

void *create_file(char *filepath);

#endif //PARSER_USER_H
