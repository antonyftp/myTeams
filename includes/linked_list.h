/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#ifndef MYTEAMSPARSER_LINKED_LIST_H
#define MYTEAMSPARSER_LINKED_LIST_H

#include <uuid/uuid.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct linked_list_s {
    void *data;
    struct linked_list_s *next;
} linked_list_t;

typedef linked_list_t user_list_t;
typedef linked_list_t message_list_t;
typedef linked_list_t thread_list_t;
typedef linked_list_t channel_list_t;
typedef linked_list_t team_list_t;
typedef linked_list_t private_message_list_t;

typedef struct user_s {
    char *username;
    uuid_t id;
    int status;
} user_t;

typedef struct message_s {
    user_t *sender;
    char *message;
    time_t timestamp;
} message_t;

typedef struct thread_s {
    char *title;
    uuid_t id;
    user_t *owner;
    char *original_post;
    message_list_t *message;
    time_t timestamp;
} thread_t;

typedef struct channel_s {
    char *title;
    uuid_t id;
    char *description;
    thread_list_t *threads;
} channel_t;

typedef struct team_s {
    char *title;
    uuid_t id;
    char *description;
    user_t *owner;
    user_list_t *users;
    channel_list_t *channels;
} team_t;

typedef struct private_message_s {
    user_t *first_user;
    user_t *second_user;
    message_list_t *message_list;
} private_message_t;

linked_list_t *add_node(linked_list_t *list_head, void *data);
user_t *find_user_by_uuid(user_list_t *list_head, uuid_t uuid);
thread_t *find_thread_by_uuid(thread_list_t *list_head, uuid_t uuid);
channel_t *find_channel_by_uuid(channel_list_t *list_head, uuid_t uuid);
team_t *find_team_by_uuid(team_list_t *list_head, uuid_t uuid);
user_t *find_user_by_name(user_list_t *list_head, char *name);
thread_t *find_thread_by_title(thread_list_t *list_head, char *title);
channel_t *find_channel_by_title(channel_list_t *list_head, char *title);
team_t *find_team_by_title(team_list_t *list_head, char *title);
int linked_list_len(linked_list_t *list_head);
linked_list_t *remove_node(linked_list_t *list_head, void *node);
private_message_t *find_private_message(private_message_list_t *list_head,
                                        uuid_t first_sender,
                                        uuid_t second_sender);

#endif //MYTEAMSPARSER_LINKED_LIST_H