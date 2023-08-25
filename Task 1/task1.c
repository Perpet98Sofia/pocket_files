#include "main.h"

int main(void)
{
	int is_interact = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
	int status;
    size_t buf_size = 0;
	char *args[] = { "", NULL}, *command;

    while (1)
    {
        if (is_interact)
            printf("$ "); /* Display the prompt */
        fflush(stdout);

        if (getline(&command, &buf_size, stdin) == -1)
            break; /* Handle Ctrl+D (End of file) */

        size_t command_length = strlen(command);
        if (command[command_length - 1] == '\n')
            command[command_length - 1] = '\0';

        pid_t pid = fork();  /* Fork a new process */

        if (pid == 0)
        {
            args[0] = command;
            execve(command, args, NULL);
            perror("./shell");
            exit(1);
        }
        else if (pid > 0)
            waitpid(pid, &status, 0); /* Wait for the child process to complete */
        else
            perror("Fork failed");
    }

    return 0;
}
