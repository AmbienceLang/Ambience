#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define HEADER_TEXT "/*\n * Copyright (c) 2024 Ambiance Programming Language.\n"\
                    " * All rights reserved.\n * This file is part of the Ambiance Programming Language project,\n"\
                    " * and is protected by copyright law.\n * Unauthorized copying of this file, via any medium is strictly prohibited.\n */\n\n"

int has_header(FILE *file) {
    rewind(file);
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, HEADER_TEXT) == 0) return 1;
    }
    return 0;
}

void add_header(FILE *file) {
    if (has_header(file)) return;
    char buffer[1024];
    FILE *temp = tmpfile();
    fputs(HEADER_TEXT, temp);
    rewind(file);
    while(fgets(buffer, sizeof(buffer), file)) fputs(buffer, temp);
    rewind(temp);
    rewind(file);
    while(fgets(buffer, sizeof(buffer), temp)) fputs(buffer, file);
    fclose(temp);
}

int has_extension(const char *filename, const char *extension) {
    const char *dot = strrchr(filename, '.');
    return dot && strcmp(dot, extension) == 0;
}

void process_directory(const char *dirpath) {
    DIR *dir = opendir(dirpath);
    if (!dir) return;
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dirpath, entry->d_name);
        struct stat statbuf;
        if (stat(path, &statbuf) == -1) continue;
        if (S_ISDIR(statbuf.st_mode)) process_directory(path);
        else if (S_ISREG(statbuf.st_mode)) {
            if (has_extension(entry->d_name, ".c") || has_extension(entry->d_name, ".amb")) {
                FILE *file = fopen(path, "r+");
                if (!file) continue;
                add_header(file);
                fclose(file);
                printf("Copyright header added to %s successfully.\n", path);
            }
        }
    }
    closedir(dir);
}
