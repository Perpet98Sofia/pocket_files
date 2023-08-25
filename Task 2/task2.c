#include "main.h"

int main(void)
{
    int is_interact = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
    int status;
    char *input, *args[MAX_ARGS];
    size_t input_length, buf_size = 0;
    pid_t pid;

    while (1)
    {
        if (is_interact)
            printf("$ ");

        if (getline(&input, &buf_size, stdin) == -1)
            break;

        /* Parse command and arguments */
        _split_line(input, args);

        pid = fork();
        if (pid == 0)
        {
            execve(args[0], args, NULL);
            perror("./shell");
            exit(1);
        }
        else if (pid > 0)
            waitpid(pid, &status, 0);
        else
            perror("Fork failed");
    }

    return 0;
}