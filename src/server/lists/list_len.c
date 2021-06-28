/*
** EPITECH PROJECT, 2021
** Project
** File description:
** list_len.cpp
*/

#include "../../includes/linked_list.h"

int linked_list_len(linked_list_t *list_head)
{
    int len = 0;

    for (; list_head; list_head = list_head->next)
        ++len;
    return (len);
}