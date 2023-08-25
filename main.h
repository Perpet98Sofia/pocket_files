#ifndef MAIN_H
#define MAIN_H

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>

void handle_sigint(int sig);
void _split_line(char *line, char *argv[]);
char *find_cmd(const char *buffer);
char *find_executable(const char *command, char **envp);
char *make_cmd(char *entry, char *exec);
void built_in_exit(char *args[]);
int _strncmp(char *s1, char *s2, int n);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif