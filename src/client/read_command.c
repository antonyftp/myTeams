/*
** EPITECH PROJECT, 2021
** B-NWP-400-STG-4-1-myteams-antony.fantapie
** File description:
** read_command.c
*/

#include "client.h"

static char *commands_names[] = { "600", "601", "602", "603", "604", "605",
    "606", "607", "608", "609", "610", "611",
    "612", "613", "614", "615", "616", "617",
    "618", "619", "620", "621", "622", "623",
    "624", "625", "626", "627", "628", "629", "200", NULL };

static void (*function[])(char **args, client_t *client) =
{
    &client_event_logged_in_handler, &client_event_logged_out_handler,
    &client_event_private_message_received_handler,
    &client_event_thread_reply_received_handler,
    &client_event_team_created_handler, &client_event_channel_created_handler,
    &client_event_thread_created_handler, &client_print_users_handler,
    &client_print_teams_handler, &client_team_print_channels_handler,
    &client_channel_print_threads_handler,
    &client_thread_print_replies_handler,
    &client_private_message_print_messages_handler,
    &client_error_unknown_team_handler, &client_error_unknown_channel_handler,
    &client_error_unknown_thread_handler, &client_error_unknown_user_handler,
    &client_error_unauthorized_handler, &client_error_already_exist_handler,
    &client_print_user_handler, &client_print_team_handler,
    &client_print_channel_handler, &client_print_thread_handler,
    &client_print_team_created_handler, &client_print_channel_created_handler,
    &client_print_thread_created_handler, &client_print_reply_created_handler,
    &client_print_subscribed_handler, &client_print_unsubscribed_handler,
    &force_logout, &logout, NULL
};

void read_command(client_t *client, char *command, char **splited_commmand)
{
    if (!splited_commmand)
        return;
    for (int i = 0; commands_names[i]; ++i)
        if (!strcasecmp(commands_names[i], splited_commmand[0]))
            function[i](splited_commmand, client);
    free_tab(splited_commmand);
}