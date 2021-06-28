/*
** EPITECH PROJECT, 2024
** Parser
** File description:
** Created by antonyftp
*/

#include "loader.h"

static void set_original_timestamp(char *timestamp, thread_t *thread)
{
    struct tm time = { 0 };

    strptime(timestamp, "%Y-%m-%d %H:%M:%S", &time);
    thread->timestamp = mktime(&time);
}

static void set_answer_timestamp(message_t *message, FILE *file)
{
    struct tm time = { 0 };
    char *line = NULL;
    size_t size = 0;

    getline(&line, &size, file);
    line[19] = '\0';
    strptime(line, "%Y-%m-%d %H:%M:%S", &time);
    message->timestamp = mktime(&time);
}

static message_t *set_answer_infos(char **splitted_message, user_list_t *users,
    char *new_line, FILE *file)
{
    message_t *message = malloc(sizeof(message_t));

    for (; *new_line != ','; ++new_line);
    new_line[strlen(new_line) - 1] = '\0';
    ++new_line;
    message->sender = find_user_by_name(users, splitted_message[0]);
    message->message = strdup(new_line);
    set_answer_timestamp(message, file);
    free(splitted_message);
    return (message);
}

static thread_t *set_thread_infos(char **splited_thread, user_list_t *users,
    FILE *file)
{
    thread_t *thread_infos = malloc(sizeof(thread_t));
    char *line = NULL;
    char *new_line = NULL;
    size_t size = 0;

    thread_infos->title = strdup(splited_thread[0]);
    uuid_parse(splited_thread[1], thread_infos->id);
    thread_infos->owner = find_user_by_name(users, splited_thread[2]);
    set_original_timestamp(splited_thread[3], thread_infos);
    thread_infos->original_post = strdup(splited_thread[4]);
    thread_infos->message = NULL;
    for (int index = 0; getline(&line, &size, file) != -1
    && strcmp(line, "\n") != 0; index++) {
        new_line = strdup(line);
        thread_infos->message = add_node(thread_infos->message,
            set_answer_infos(split_string(line, ",\n"), users, new_line,
                file));
    }
    return (thread_infos);
}

thread_list_t *load_thread(user_list_t *users)
{
    thread_list_t *thread_list_head = NULL;
    FILE *file = open_file(THREADS_FILEPATH, "r");
    size_t size = 0;
    char *line = NULL;
    char **splitted_thread = NULL;

    if (file == (FILE *)-1)
        return (create_file(THREADS_FILEPATH));
    getline(&line, &size, file);
    while (getline(&line, &size, file) != -1) {
        splitted_thread = split_string(line, ";\n");
        thread_list_head = add_node(thread_list_head,
            set_thread_infos(splitted_thread, users, file));
        free_tab(splitted_thread);
    }
    free(line);
    fclose(file);
    return (thread_list_head);
}