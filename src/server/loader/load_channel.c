/*
** EPITECH PROJECT, 2024
** Parser
** File description:
** Created by antonyftp
*/

#include "loader.h"

static channel_t *set_channel_infos(char **splitted_channels,
    thread_list_t *thread)
{
    channel_t *channel_infos = malloc(sizeof(channel_t));
    char **splitted_threads = NULL;
    uuid_t thread_uuid;

    channel_infos->title = strdup(splitted_channels[0]);
    uuid_parse(splitted_channels[1], channel_infos->id);
    channel_infos->description = strdup(splitted_channels[2]);
    splitted_threads = split_string(splitted_channels[3], ",\n");
    channel_infos->threads = NULL;
    for (int index = 0; index < tab_len(splitted_threads); index++) {
        uuid_parse(splitted_threads[index], thread_uuid);
        channel_infos->threads = add_node(channel_infos->threads,
            find_thread_by_uuid(thread, thread_uuid));
    }
    if (splitted_threads != NULL)
        free_tab(splitted_threads);
    return (channel_infos);
}

channel_list_t *load_channel(thread_list_t *thread)
{
    channel_list_t *channel_list_head = NULL;
    FILE *file = open_file(CHANNELS_FILEPATH, "r");
    size_t size = 0;
    char *line = NULL;
    char **splitted_channels = NULL;

    if (file == (FILE *)-1)
        return (create_file(CHANNELS_FILEPATH));
    getline(&line, &size, file);
    while (getline(&line, &size, file) != -1) {
        splitted_channels = split_string(line, ";\n");
        channel_list_head = add_node(channel_list_head,
            set_channel_infos(splitted_channels, thread));
        free_tab(splitted_channels);
    }
    free(line);
    fclose(file);
    return (channel_list_head);
}