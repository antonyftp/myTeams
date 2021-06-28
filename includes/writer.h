/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** writer.h
*/

#ifndef MYTEAMSPARSER_WRITER_H
#define MYTEAMSPARSER_WRITER_H

#include <uuid/uuid.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"

#define USER_PATH "savefiles/users.cache"
#define THREAD_PATH "savefiles/threads.cache"
#define TEAM_PATH "savefiles/teams.cache"
#define PRIVATE_MESSAGE_PATH "savefiles/privatemessages.cache"
#define CHANNEL_PATH "savefiles/channels.cache"

#define RIGHT_THREAD tab_len((splitted_line = split_string(strdup(line), \
";"))) > 1 && !strcmp(splitted_line[1], uuid)

/**
** @brief Must be called when you create a new user
** @param username The username of the new user
** @param uuid The id of the new user
** @return 0 when it successfully write in the file, otherwise -1
**/
int add_user(char *username, uuid_t uuid);

/**
** @brief Must be called when you create a new thread
** @param title The title of the new thread
** @param uuid The id of the new thread
** @param owner The owner of the new thread
** @param message The message of the new thread
** @return 0 when it successfully write in the file, otherwise -1
**/
int add_thread(char *title, uuid_t uuid, char *owner, char *message);

/**
** @brief Must be called when you create a new team
** @param title The title of the new team
** @param uuid The id of the new team
** @param description The description of the new team
** @param owner The owner of the new team
** @return 0 when it successfully write in the file, otherwise -1
**/
int add_team(char *title, uuid_t uuid, char *description, char *owner);

/**
** @brief Must be called when you create a new channel
** @param title The title of the new channel
** @param uuid The id of the new channel
** @param description The description of the new channel
** @param owner The owner of the new channel
** @return 0 when it successfully write in the file, otherwise -1
**/
int add_channel(char *title, uuid_t uuid, char *description);

/**
** @brief Must be called when a user send a private message
** @param first The username of the person who send the message
** @param second The username of the person who receive the message
** @param message The message
** @param timestamp The timestamp of the message
** @return 0 when it successfully write in the file, otherwise -1
**/
int add_private_message(char *first, char *second, char *message,
                        time_t timestamp);

/**
** @breif Must be called when a user answer to a thread
** @param uuid The id of the thread
** @param username The username of the person how answer
** @param answer The answer
** @return 0 when it successfully write in the file, otherwise -1
**/
int add_thread_answer(uuid_t uuid, char *username, char *answer,
    time_t timestamp);

/**
** @breif Must be called when a user subscribe to a team
** @param uuid The id of the team
** @param username The username of the user
** @return 0 when it successfully write in the file, otherwise -1
**/
int team_subscribe(uuid_t uuid, char *username);

/**
* @breif Must be called when a user subscribe to a channel
* @param uuid The id of the channel
* @param username The username of the user
* @return 0 when it successfully write in the file, otherwise -1
*/
int channel_subscribe(uuid_t uuid, char *username);

/**
* @breif Must be called when a user unsubscribe to a team
* @param uuid The id of the team
* @param username The username of the user
* @return 0 when it successfully write in the file, otherwise -1
*/
int team_unsubscribe(uuid_t uuid, char *username);

/**
* @breif Must be called when a user unsubscribe to a channel
* @param uuid The id of the channel
* @param username The username of the user
* @return 0 when it successfully write in the file, otherwise -1
*/
int channel_unsubscribe(uuid_t uuid, char *username);

/**
* @breif Must be called juste after add_channel function in order to add it in
* the parent team
* @param uuid The id of the parent team
* @param channel_uuid The id of the new channel
*/
void set_channel_parent(uuid_t uuid, uuid_t channel_uuid);

/**
* @breif Must be called juste after add_thread function in order to add it in
* the parent channel
* @param uuid The id of the parent channel
* @param thread_uuid The id of the new thread
*/
void set_thread_parent(uuid_t uuid, uuid_t thread_uuid);

void find_private_message_part(char **names_tab, char **begening, char **end,
    int *new_conv);
void add_line_to_var(char *file_content, char *line, int *index);
void add_thread_channel_to_upper(char *filepath, uuid_t uuid,
    uuid_t child_uuid);
char *concat_str(char *str1, char *str2);
void print_file(FILE *file, int new_conv, char *beg, char *names);
int free_buf(char *end, FILE *file, char *beg);
void update_var(char *file_begening, int *index, int *right_thread,
    int *end);

#endif //MYTEAMSPARSER_WRITER_H