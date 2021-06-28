/*
** EPITECH PROJECT, 2021
** Project
** File description:
** linked_list.c
*/

#include "../../includes/linked_list.h"

linked_list_t *add_node(linked_list_t *list_head, void *data)
{
    linked_list_t *tmp = list_head;

    if (!list_head) {
        list_head = malloc(sizeof(linked_list_t));
        list_head->data = data;
        list_head->next = NULL;
    } else {
        for (; tmp->next; tmp = tmp->next);
        tmp->next = malloc(sizeof(linked_list_t));
        tmp = tmp->next;
        tmp->next = NULL;
        tmp->data = data;
    }
    return (list_head);
}