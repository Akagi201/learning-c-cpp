#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "strsplit.h"
#include "trim.h"
#include "substr.h"
#include "hash.h"

#define OBJECT_STR "Object"
#define PROPERTY_STR "Property"
#define NUMBER_STR "Number"
#define STRING_STR "String"
#define BOOLEAN_STR "Boolean"

char textbuf[2048];

typedef struct metadata_property_s {
    char type[16];
    char value[256];
} metadata_property_t;

typedef struct metadata_s {
    hash_t *meta;
    int len;
} metadata_t;

// 0: success / not 0: fail
void parse_metadata(char *meta_str, metadata_t *metadata) {
    if (NULL == meta_str || NULL == metadata) {
        return;
    }

    char *line = NULL;

    line = strtok(strdup(textbuf), "\n");
    metadata_property_t meta_property;
    memset(metadata, 0, sizeof(metadata_t));
    memset(&meta_property, 0, sizeof(meta_property));
    metadata->meta = hash_new();

    char *parts[256] = {NULL};
    int size = 0;

    char *line_parts[256] = {NULL};
    int line_size = 0;
    char *key = NULL;
    char *type = NULL;
    char *value = NULL;

    size = strsplit(textbuf, parts, "\n");

    for (int i = 0; i < size; i++) {
//        printf("%s\n", trim(parts[i]));
        line_size = strsplit(trim(parts[i]), line_parts, " ");

        if (0 == strcmp(line_parts[0], OBJECT_STR)) {
            // printf("%s\n", substr(line_parts[1], 1, -1));
            metadata->len = atoi(substr(line_parts[1], 1, -1));
//            printf("%d\n", metadata->len);
        } else if (0 == strcmp(line_parts[0], PROPERTY_STR)) {
            key = substr(line_parts[1], 1, strlen(line_parts[1]) - 1);
            type = line_parts[2];
            value = line_parts[3];

//            printf("key: %s, len: %lu\n", key, strlen(key));
//            printf("type: %s, len: %lu\n", type, strlen(type));
//            printf("value: %s, len: %lu\n", value, strlen(value));

            metadata_property_t *meta_property = (metadata_property_t *)calloc(1, sizeof(metadata_property_t));

            memcpy(meta_property->type, type, strlen(type));
            memcpy(meta_property->value, value, strlen(value));

            hash_set(metadata->meta, key, (void *)meta_property);
        }

        for (int i = 0; i < line_size; i++) {
            free(line_parts[i]);
        }
    }

    for (int i = 0; i < size; i++) {
        free(parts[i]);
    }
}

void print_metadata(const metadata_t *metadata) {
    printf("print metadata begin\n");
    if (NULL == metadata) {
        return;
    }
    metadata_property_t *meta_property = NULL;
    printf("len: %d\n", metadata->len);

    hash_each(metadata->meta, {
        meta_property = (metadata_property_t *) val;
        printf("key: %s, type: %s, value: %s\n", key, meta_property->type, meta_property->value);
    });
    printf("print metadata end\n");
}

void free_metadata(metadata_t *metadata) {
    if (NULL == metadata) {
        return;
    }
    metadata_property_t *meta_property = NULL;
    hash_each_val(metadata->meta, {
        meta_property = (metadata_property_t *) val;
        free(meta_property);
    });
    hash_free(metadata->meta);
}

int main() {
    char *line = NULL;
    FILE *fp = NULL;

    fp = fopen("meta.txt", "r");
    memset(textbuf, 0, sizeof(textbuf));
    fread(textbuf, 1, sizeof(textbuf), fp);

    metadata_t metadata;
    memset(&metadata, 0, sizeof(metadata));

    parse_metadata(textbuf, &metadata);
    print_metadata(&metadata);
    free_metadata(&metadata);

    return 0;
}
