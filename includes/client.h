/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#ifndef B_NWP_400_STG_4_1_MYTEAMS_ANTONY_FANTAPIE_CLIENT_H
#define B_NWP_400_STG_4_1_MYTEAMS_ANTONY_FANTAPIE_CLIENT_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include "logging_client.h"

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
#define NOT_LOGGEDIN 0
#define LOGGEDIN 1
#define QUIT 0
#define CONTINUE 1
#define HELP "/login[\"user_name\" ]: set the user_name used by client\n\
/logout: disconnect the client from the server\n\
/users: get the list of all users that exist on the domain\n\
/user [\"user_uuid\"]: get information about a user\n\
/send [\"user_uuid\"][\"message_body\"]: send a message to a user\n\
/messages [\"user_uuid\"]: list all messages exchange with an user\n\
/subscribe [\"team_uuid\"] : subscribe to the event of a team and its sub \
directories (enable reception of all events from a team)\n\
/subscribed? [\"team_uuid\"]: list all subscribed teams or list all users \
subscribed to a team\n\
/unsubscribe [\"team_uuid\"]: unsubscribe from a team\n\
/use? [\"team_uuid\"]?[\"channel_uuid\"]?[\"thread_uuid\"]: use specify a \
context team/channel/thread\n\
/create: based on what is being used create the sub resource (see below)\n\
/list: based on what is being used list all the sub resources (see below)\n\
/info: based on what is being used list the current (see below)\n\n\
/create:\n\
When the context is not defined (/use):\n\
\t- /create [\"team_name\"] [\"team_description\"]: create a new team\n\
When team_uuid is defined (/use \"team_uuid\"):\n\
\t- /create [\"hannel_name\"][\"channel_description\"]: create a new channel\n\
When team_uuid and channel_uuid are defined (/use \"team_uuid\" \
\"channel_uuid\"):\n\
\t- /create [\"thread_title\"] [\"thread_message\"]: creat e anew thread\n\
When team_uuid, channel_uuid and thread_uuid are defined (/use \"team_uuid\" \
\"channel_uuid\" \"thread_uuid\"):\n\
\t- /create [\"comment_body\"]: create a new reply\n\n\
/list:\n\
When the context is not defined (/use):\n\
\t- /list: list all existing teams\n\
When team_uuid is defined (/use \"team_uuid\"):\n\
\t- /list: list all existing channels\n\
When team_uuid and channel_uuid are defined (/use \"team_uuid\" \
\"channel_uuid\"):\n\
\t- /list: list all existing threads\n\
When team_uuid, channel_uuid and thread_uuid are defined (/use \"team_uuid\" \
\"channel_uuid\" \"thread_uuid\"):\n\
\t- /list: list all existing replies\n\n\
/info:\n\
When the context is not defined (/use):\n\
\t- /info: display currently logged user infos\n\
When team_uuid is defined (/use \"team_uuid\"):\n\
\t- /info: display currently selected team infos\n\
When team_uuid and channel_uuid are defined (/use \"team_uuid\" \
\"channel_uuid\"):\n\
\t- /info: display currently selected channel infos\n\
When team_uuid, channel_uuid and thread_uuid are defined (/use \"team_uuid\" \
\"channel_uuid\" \"thread_uuid\"):\n\
\t- /info: display currently selected thread infos\n"
#define MUST_BE_LOGGED "You must be logged in to use this function.\n"
#define ALREADY_LOGGEDIN "You are already logged in.\n"
#define AGRS_NOT_IMPLEMENTED "%s is not implemented for those arguments. Use \
/help for more informations.\n"
#define ERROR_CREATE_SOCKET "Error while creating socket.\n"
#define ERROR_CONNECT_SERVER "Can't connect to the server.\n"
#define INVALID_ARGS "Invalid args.\n"
#define SHOULD_TRY_AGAIN "Something went wrong. Try Again.\n"
#define HELPER "USAGE:\t./myteams_cli ip port\n\t\tip\tis the server ip \
address on which the server socket listens\n\t\tport\tis the port number on \
which the server socket listens\n"

typedef struct client_s {
    int socket_fd;
    int is_loggin;
    int quit;
} client_t;

char *strptime(const char *s, const char *format, struct tm *tm);
void new_client(client_t *client, int socket_fd);
int is_number(char *str);
int client(char *ip, int port);
int init_connection(char *ip, int port);
int handle_client(fd_set *rdfs, client_t *clients);
char *get_line(int fd);
void send_command(client_t *client, char *command, char **splited_commmand);
char **split_string(char *str, char *tok);
int tab_len(char **tab);
void free_tab(char **tab);
void no_arg(client_t *client, char *command, char **splited_commmand);
void one_arg(client_t *client, char *command, char **splited_commmand);
void two_arg(client_t *client, char *command, char **splited_commmand);
void no_or_one_arg(client_t *client, char *command, char **splited_commmand);
void undefined_arg(client_t *client, char *command, char **splited_commmand);
void send_logout(client_t *client, char *command, char **splited_commmand);
void read_command(client_t *client, char *command, char **splited_commmand);
time_t char_to_time(char *str);
char **split_args(char *args);

void client_channel_print_threads_handler(char **args, client_t *client);
void client_error_already_exist_handler(char **args, client_t *client);
void client_error_unauthorized_handler(char **args, client_t *client);
void client_error_unknown_channel_handler(char **args, client_t *client);
void client_error_unknown_team_handler(char **args, client_t *client);
void client_error_unknown_thread_handler(char **args, client_t *client);
void client_error_unknown_user_handler(char **args, client_t *client);
void client_event_channel_created_handler(char **args, client_t *client);
void client_event_logged_in_handler(char **args, client_t *client);
void client_event_logged_out_handler(char **args, client_t *client);
void client_event_private_message_received_handler(char **args,
    client_t *client);
void client_event_team_created_handler(char **args, client_t *client);
void client_event_thread_created_handler(char **args, client_t *client);
void client_event_thread_reply_received_handler(char **args, client_t *client);
void client_print_channel_created_handler(char **args, client_t *client);
void client_print_channel_handler(char **args, client_t *client);
void client_print_reply_created_handler(char **args, client_t *client);
void client_print_subscribed_handler(char **args, client_t *client);
void client_print_team_created_handler(char **args, client_t *client);
void client_print_team_handler(char **args, client_t *client);
void client_print_teams_handler(char **args, client_t *client);
void client_print_thread_created_handler(char **args, client_t *client);
void client_print_thread_handler(char **args, client_t *client);
void client_print_unsubscribed_handler(char **args, client_t *client);
void client_print_user_handler(char **args, client_t *client);
void client_print_users_handler(char **args, client_t *client);
void client_private_message_print_messages_handler(char **args,
    client_t *client);
void client_team_print_channels_handler(char **args, client_t *client);
void client_thread_print_replies_handler(char **args, client_t *client);
void force_logout(char **args, client_t *client);
void logout(char **args, client_t *client);

#endif //B_NWP_400_STG_4_1_MYTEAMS_ANTONY_FANTAPIE_CLIENT_H
