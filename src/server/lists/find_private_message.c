/*
** EPITECH PROJECT, 2021
** Project
** File description:
** find_private_message.c
*/

#include "../../includes/linked_list.h"

private_message_t *find_private_message(private_message_list_t *list_head,
    uuid_t first_sender, uuid_t second_sender)
{
    for (; list_head; list_head = list_head->next)
        if ((!uuid_compare(first_sender,
            ((private_message_t *)list_head->data)->first_user->id)
        && !uuid_compare(second_sender,
            ((private_message_t *)list_head->data)->second_user->id))
        || (!uuid_compare(second_sender,
            ((private_message_t *)list_head->data)->first_user->id)
        && !uuid_compare(first_sender,
            ((private_message_t *)list_head->data)->second_user->id)))
            return ((private_message_t *)list_head->data);
    return (NULL);
}