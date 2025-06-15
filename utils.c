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

void    ft_exit_chk(t_list *mini, char *input)
{
    if (!input)
    {
        free(mini->path);
        free(mini);
        exit(0);
    }
    if (!ft_strncmp(input, "exit", 4))
    {
        free(input);
        free(mini->path);
        free(mini);
        exit(0);
    }
}

void ft_builtins(t_list *mini, t_cmd *cmds, char **env)
{
    if (ft_strncmp(cmds->command[0], "echo", 4) == 0)
    {
        ft_echo(cmds->command, cmds->num, mini->input);
        return;
    }
    if (ft_strncmp(cmds->command[0], "cd", 2) == 0)
    {
        ft_cd(cmds->command, mini);
        return;
    }
    if (ft_strncmp(cmds->command[0], "export", 6) == 0)
    {
        ft_exp (env, cmds);
        return;
    }
    if (ft_strncmp(cmds->command[0], "unset", 5) == 0)
    {
        ft_unset(env, cmds->command[1]);
        return;
    }
    ft_cmds(mini, env, cmds->command);

}