#include "main.h"

int main(int ac, char **av, char *envp[])
{
    char *input, *args[MAX_ARGS];
    char *cmd, *abs_cmd, *exec;
    size_t input_length, buf_size = 0;
    pid_t pid;
    int found = -1, status;

    while (1)
    {
        printf("$ ");

        if (getline(&input, &buf_size, stdin) == -1)
            break;

        input_length = strlen(input);
        if (input[input_length - 1] == '\n')
            input[input_length - 1] = '\0';

        _split_line(input, args);

        /* Check for exit built-in command */
        if (_strcmp(args[0], "exit") == 0)
            built_in_exit(args);

        if (access(input, X_OK) == 0)
            found = 1;
		else
		{
			cmd = find_cmd(input);
			exec = find_executable(cmd, envp);
			if (exec)
            {
                found = 1;
                abs_cmd = make_cmd(input, exec);
				args[0] = strdup(abs_cmd);
            }
		}
        if (found == 1)
        {
            pid = fork();
            if (pid == 0)
            {
                execve(args[0], args, NULL);
                perror("./shell");
                exit(1);
            } else if (pid > 0) {
                waitpid(pid, &status, 0);
            } else
                perror("Fork failed");
        }
        else
        {
            perror("./shell");
            exit(1);
        }
    }

    return 0;
}
