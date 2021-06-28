/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#ifndef B_NWP_400_STG_4_1_MYTEAMS_ANTONY_FANTAPIE_SERVER_H
#define B_NWP_400_STG_4_1_MYTEAMS_ANTONY_FANTAPIE_SERVER_H

#include "logging_server.h"
#include "linked_list.h"
#include "writer.h"
#include "loader.h"
#include <stdbool.h>
#include <stdlib.h>
#include <netdb.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <uuid/uuid.h>

#define CODE530 "530 Not logged in.\r\n"
#define CODE450 "450 Requested file action not taken.\r\n"
#define CODE250 "250 Requested file action okay, completed.\r\n"
#define CODE501 "501 Syntax error in parameters or arguments.\r\n"
#define CODE331 "331 User name okay, need password.\r\n"
#define CODE230 "230 User logged in, proceed.\r\n"
#define CODE430 "430 Invalid username or password.\r\n"
#define CODE332 "332 Need account for login.\r\n"
#define CODE221 "221 Service closing control connection.\r\n"
#define CODE214 "214 Help message.\r\n"
#define CODE500 "500 Syntax error in parameters or arguments\r\n"
#define CODE220 "220 Service ready for new user.\r\n"
#define CODE200 "200 The requested action has been successfully completed.\r\n"
#define CODE425 "425 Can't open data connection\r\n"
#define CODE125 "125 File status okay; about to open data connection.\r\n"
#define CODE226 "226 Closing data connection.\r\n"
#define CODE553 "553 Requested action not taken. File name not allowed.\r\n"

#define CLIENT_MAX 30

#define MAIN_SOCKET my_team->server.sockets.main_socket
#define RCV_SOCKET my_team->server.sockets.receive_socket

#define READFDS my_team->server.fdset.readfds
#define WRITEFDS my_team->server.fdset.writefds

#define MAXSD my_team->server.socket_descriptor.max_sd
#define SD_SERVER server.socket_descriptor.sd
#define SD my_team->server.socket_descriptor.sd

#define CMD_PTR commands[i].cmd

#define CLIENT my_team->server.client[i]
#define CLIENT_J my_team->server.client[j]

#define IS_SPACE(c) (c == ' ')

#define IS_GOOD_CLIENT clients[index].connected && index != i && \
find_user_by_uuid(team->users, clients[index].user->id) != NULL

#define FIND_THREAD find_thread_by_uuid(find_channel_by_uuid( \
find_team_by_uuid(my_team->teams, CLIENT.team_uuid)->channels, \
CLIENT.channel_uuid)->threads, CLIENT.thread_uuid)

#define SEND_SOCKET_REPLY dprintf(CLIENT.fd, \
"611 \"%s\" \"%s\" \"%s\" \"%s\"\n", id, user_id, \
convert_timestamp(((message_t *)list->data)->timestamp), \
((message_t *)list->data)->message);

enum Use {
    Nothing = 0,
    Team = 1,
    Channel = 2,
    Thread = 3
};

struct client_t {
    int fd;
    user_t *user;
    bool connected;
    enum Use use_status;
    uuid_t team_uuid;
    uuid_t channel_uuid;
    uuid_t thread_uuid;
};

struct user_t {
    uuid_t id;
    char *username;
    struct user_t *next;
};

struct fdset_t {
    fd_set readfds;
    fd_set writefds;
};

struct socket_t {
    int main_socket;
    int receive_socket;
};

struct socket_descriptor_t {
    int sd;
    int max_sd;
};

struct server_t {
    struct sockaddr_in my_socket;
    struct client_t client[50];
    struct socket_t sockets;
    struct fdset_t fdset;
    struct socket_descriptor_t socket_descriptor;
    uint16_t port;
    socklen_t client_size;
};

struct thread_t {
    char *original_post;
    char **answers;
    struct thread_t *next;
    struct user_t *users;
    uuid_t id;
};

struct channel_t {
    struct thread_t *threads;
    struct user_t *users;
    struct client_t owner;
    struct channel_t *next;
    uuid_t id;
};

struct team_t {
    struct channel_t *channels;
    struct user_t *users;
    struct team_t *next;
    uuid_t id;
};

struct my_teams_t {
    team_list_t *teams;
    struct server_t server;
    user_list_t *users;
    private_message_list_t *private_message;
};

typedef struct	commands_s {
    const char *cmd;
    int	(*func_ptr)();
} commands_t;

void add_new(struct my_teams_t *my_team);
void set_server(struct my_teams_t *my_team);
void server_loop(struct my_teams_t *my_team);
void init_server(struct my_teams_t *my_team);
void main_command(struct my_teams_t *my_team);
int check_port(char *port);
void init_client(struct client_t *client, int receive);
void print_new_channel(struct my_teams_t *my_team, team_t *team, char **arg,
    int i);
void print_reply(struct my_teams_t *my_team, int i, message_t *message_struct);

int create(struct my_teams_t *my_team, char **arg, int i, int ac);
void create_new_thread(struct my_teams_t *my_team, int i, char **arg);
int info(struct my_teams_t *my_team, char **arg, int i, int ac);
int list(struct my_teams_t *my_team, char **arg, int i, int ac);
int login(struct my_teams_t *my_team, char **arg, int i, int ac);
int logout(struct my_teams_t *my_team, char **arg, int i, int ac);
int messages(struct my_teams_t *my_team, char **arg, int i, int ac);
int send_message(struct my_teams_t *my_team, char **arg, int i, int ac);
int subscribe(struct my_teams_t *my_team, char **arg, int i, int ac);
int subscribed(struct my_teams_t *my_team, char **arg, int i, int ac);
int unsubscribed(struct my_teams_t *my_team, char **arg, int i, int ac);
int use(struct my_teams_t *my_team, char **arg, int i, int ac);
int user(struct my_teams_t *my_team, char **arg, int i, int ac);
int users(struct my_teams_t *my_team, char **arg, int i, int ac);
void create_new_channel(struct my_teams_t *my_team, int i, char **arg);
void disconnect(struct my_teams_t *my_team);
void free_messages(message_list_t *list);
void free_threads(channel_list_t *channels);
void free_channel(team_list_t *teams);
void free_users_in(team_list_t *team);
void close_server(struct my_teams_t *my_team);
void uuid_parsing(thread_list_t *list, char **id, char **uid);
void uuid_parsing_reply(char **user_id, message_list_t *list);
void print_error_reply(struct my_teams_t *my_team, int i);
int unautorized(struct my_teams_t *my_team, int i);
char *convert_timestamp(time_t timestamp);

bool is_uuid(char *uuid);

struct team_t *add_teamnode(struct team_t *node, struct team_t *list);
struct team_t *remove_teamnode(uuid_t searched, struct team_t *list);
struct team_t *find_teamnode(uuid_t searched, struct team_t *list);
struct channel_t *add_channelnode(struct channel_t *node,
    struct channel_t *list);
struct channel_t *remove_channelnode(uuid_t searched, struct channel_t *list);
struct channel_t *find_channelnode(uuid_t searched, struct channel_t *list);
struct thread_t *add_threadnode(struct thread_t *node, struct thread_t *list);
struct thread_t *remove_threadnode(uuid_t searched, struct thread_t *list);
struct thread_t *find_threadnode(uuid_t searched, struct thread_t *list);
struct user_t *add_usernode(struct user_t *node, struct user_t *list);
struct user_t *remove_usernode(uuid_t searched, struct user_t *list);
struct user_t *find_usernode(uuid_t searched, struct user_t *list);
struct user_t *find_usernodebyname(char *searched, struct user_t *list);
struct client_t *add_clientnode(struct client_t *node, struct client_t *list);
struct client_t *remove_clientnode(uuid_t searched, struct client_t *list);
struct client_t *find_clientnode(uuid_t searched, struct client_t *list);
struct client_t *find_clientnodebyname(char *searched, struct client_t *list);
void do_server_command(struct my_teams_t *my_team);
int check_team(struct my_teams_t *my_team, int i);
int check_channel(struct my_teams_t *my_team, int i);
int check_thread(struct my_teams_t *my_team, int i);

char **split_args(char *args);

#endif //B_NWP_400_STG_4_1_MYTEAMS_ANTONY_FANTAPIE_SERVER_H