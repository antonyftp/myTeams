/*
** EPITECH PROJECT, 2021
** Project
** File description:
** remove.cpp
*/

#include "../../includes/linked_list.h"

linked_list_t *remove_node(linked_list_t *list_head, void *node)
{
    linked_list_t *head = list_head;
    linked_list_t *tmp = NULL;

    if (linked_list_len(list_head) == 0)
        return (NULL);
    if (list_head->data == node) {
        head = list_head->next;
        free(list_head);
        return (head);
    }
    for (; list_head->next; list_head = list_head->next) {
        if (list_head->next->data == node) {
            tmp = list_head->next;
            list_head->next = list_head->next->next;
            free(tmp);
        }
    }
    return (head);
}