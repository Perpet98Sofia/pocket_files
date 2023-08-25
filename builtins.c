#include "main.h"

void built_in_exit(char *args[])
{
    if (strcmp(args[0], "exit") == 0)
        exit(0);
}