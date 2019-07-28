/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** config
*/

#include "json.h"
#include "shell.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

OPTION(Config) parse_config(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NONE(Config);

    char *contents = read_all(fd);
    close(fd);
    if (contents == 0)
        return NONE(Config);

    json_t *data = ljson_parse(contents);
    free(contents);
    if (data == 0)
        return NONE(Config);

    json_item_t *root = data->root;
    if (root == 0)
        return NONE(Config);

    if (root->type != JSON_OBJECT)
        return NONE(Config);

    json_item_t *rc_item = lhmap_get(root->data, "rc_file");
    json_item_t *alias_item = lhmap_get(root->data, "alias_file");
    json_item_t *history_item = lhmap_get(root->data, "history_file");

    OPTION(CharPtr)
    rc_file = (rc_item->type == JSON_STRING) ?
        OPT_FROM_NULLABLE(CharPtr, strdup(rc_item->data)) :
        NONE(CharPtr);
    OPTION(CharPtr)
    alias_file = (alias_item->type == JSON_STRING) ?
        OPT_FROM_NULLABLE(CharPtr, strdup(alias_item->data)) :
        NONE(CharPtr);
    OPTION(CharPtr)
    history_file = (history_item->type == JSON_STRING) ?
        OPT_FROM_NULLABLE(CharPtr, strdup(history_item->data)) :
        NONE(CharPtr);

    putstr("rc_file: '%s'\n", rc_item->data);
    putstr("alias_file: '%s'\n", alias_item->data);
    putstr("history_file: '%s'\n", history_item->data);

    return NONE(Config);
}
