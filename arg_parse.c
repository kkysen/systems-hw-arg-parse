//
// Created by kkyse on 11/12/2017.
//

#ifndef _POSIX_C_SOURCE
    // needed for getline() header
    #define _POSIX_C_SOURCE 201711L
#endif

#ifndef _BSD_SOURCE
    // needed for strsep() header
    #define _BSD_SOURCE 201711L
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "stacktrace.h"
#include "util.h"

size_t num_spaces(const char *s) {
    size_t count = 0;
    char c;
    while ((c = *s++)) {
        if (c == ' ') {
            ++count;
        }
    }
    return count;
}

char **parse_args(char *line) {
    printf("line: '%s'\n", line);
    const size_t argc = num_spaces(line) + 1;
    printf("argc: %zu\n", argc);
    char **const argv = (char **) malloc((argc + 1) * sizeof(char *));
    for (size_t i = 0; i < argc; ++i) {
        argv[i] = strsep(&line, " ");
    }
    argv[argc] = NULL;
    return argv;
}

void print_argv(char **argv) {
    printf("argv: [");
    char *arg;
    while ((arg = *argv++)) {
        printf("%s", arg);
        if (*argv) {
            printf(", ");
        }
    }
    printf("]\n");
}

#define loop (!*line && false)

int main() {
    set_stack_trace_signal_handler();
//    printf("num_spaces: %zu\n", num_spaces("hello world"));
    
    char *line = copy_str("");
    if (!loop) {
        size_t buf_size;
        ssize_t length = getline(&line, &buf_size, stdin);
//        printf("length: %zu\n", length);
        line[length - 1] = 0;
    }
    if (!*line) {
        line = copy_str("make run");
    }
    char **argv = parse_args(line);
    printf("parsed argv\n");
    print_argv(argv);
    printf("execvp:\n\n");
    execvp(*argv, argv);
    return EXIT_FAILURE;
}