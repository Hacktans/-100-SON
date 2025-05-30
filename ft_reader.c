#include "minishell.h"

void    exec_cmds(char *full_path, char **args, char **env)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        execve(full_path, args, env);
        perror("execv");
        exit(1);
    }
    else
    {
        wait(NULL);
    }
    free(full_path);
}

void    ft_cmds(t_list *mini, char **env, char **args)
{
    char *full_path = NULL;
    char **path = mini->paths;
    int i = 0;

    while (path && path[i])
    {
        full_path = malloc(ft_strlen(path[i]) + ft_strlen(args[0]) + 2);
        if (!full_path)
            exit(EXIT_FAILURE);
        strcpy(full_path, path[i]);
        strcat(full_path, "/");
        strcat(full_path, args[0]);
        if (access(full_path, X_OK) == 0)
            break;

        free(full_path);
        full_path = NULL;
        i++;
    }
    if (!full_path)
        full_path = strdup(args[0]);
    exec_cmds(full_path, args, env);
}