/*
** EPITECH PROJECT, 2024
** B_NWP_400_STG_4_1_myteams_antony_fantapie
** File description:
** Created by antonyftp
*/

#include "server.h"

static int send_error(struct my_teams_t *my_team, char **arg, int i)
{
    dprintf(my_team->server.client[i].fd, "616 \"%s\"\n", arg[1]);
    return (0);
}

static void print_send_message(message_t *message, user_t *sender,
    user_t *receiver, struct my_teams_t *my_team)
{
    char *sender_uuid = malloc(sizeof(char) * 37);
    char *receiver_uuid = malloc(sizeof(char) * 37);
    int index = -1;

    uuid_unparse(sender->id, sender_uuid);
    uuid_unparse(receiver->id, receiver_uuid);
    server_event_private_message_sended(sender_uuid, receiver_uuid,
                                        message->message);
    for (int i = 0; i < 50; ++i)
        if (my_team->server.client[i].connected
        && !uuid_compare(receiver->id, my_team->server.client[i].user->id)) {
            index = i;
            break;
        }
    if (index != -1)
        dprintf(my_team->server.client[index].fd, "602 \"%s\" \"%s\"\n",
            sender_uuid,
            message->message);
    free(sender_uuid);
    free(receiver_uuid);
}

private_message_t *init_conv(struct my_teams_t *my_team, user_t *target, int i)
{
    private_message_t *conv = find_private_message(
            my_team->private_message,
            my_team->server.client[i].user->id, target->id);

    if (!conv) {
        conv = malloc(sizeof(private_message_t));
        conv->message_list = NULL;
        conv->first_user = my_team->server.client[i].user;
        conv->second_user = target;
    }
    return (conv);
}

static int end_send(message_t *message, struct my_teams_t *my_team, int i,
    user_t *target)
{
    print_send_message(message, my_team->server.client[i].user, target,
        my_team);
    add_private_message(my_team->server.client[i].user->username,
        target->username, message->message, message->timestamp);
    return (0);
}

int send_message(struct my_teams_t *my_team, char **arg, int i, int ac)
{
    uuid_t uuid;
    user_t *target;
    private_message_t *conv = NULL;
    message_t *message;

    uuid_parse(arg[1], uuid);
    target = find_user_by_uuid(my_team->users, uuid);
    if (!target)
        return (send_error(my_team, arg, i));
    if (strlen(arg[2]) > 512)
        return (-1);
    conv = init_conv(my_team, target, i);
    message = malloc(sizeof(message_t));
    message->message = strdup(arg[2]);
    message->timestamp = time(NULL);
    message->sender = my_team->server.client[i].user;
    conv->message_list = add_node(conv->message_list, message);
    my_team->private_message = add_node(my_team->private_message, conv);
    return (end_send(message, my_team, i, target));
}