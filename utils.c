#include "minishell.h"

void paths(char **env, t_list *mini)
{
    int i = 0;
    while (env[i])
    {
        if (ft_strncmp("PATH=", env[i], 5) == 0)
            mini->path = strdup(env[i] + 5);
        if (ft_strncmp("HOME=", env[i], 5) == 0)
            mini->home = strdup(env[i] + 5);
        i++;
    }
    mini->paths = ft_split(mini->path, ':');
}

void handle_sig(int signum)
{
    (void)signum;
    write(1, "\n", 1);
    //rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

