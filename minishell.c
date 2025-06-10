#include "minishell.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_list *mini;
    t_token *tokens = NULL;
    t_cmd *cmd;
    char *input;
    mini = malloc(sizeof(t_list));
    if (!mini)
        return (0);
    ft_memset(mini, 0, sizeof(t_list));
    paths(env, mini);
    signal(SIGINT, handle_sig); 
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        input = readline("minishell$ ");
        ft_exit_chk(mini, input);
        add_history(input);
        ft_token(input, &tokens);
        if(!syntax_chk(tokens, input))
        {
            exit_code = 258;
            printf("Syntax Error\n");
            reset_tokens(tokens);
            tokens = NULL;
            continue;
        }
        cmd = ft_parsing(tokens, mini);
        reset_tokens(tokens);
        tokens = NULL;
        if(cmd == NULL)
            continue;
        ft_builtins(mini, cmd, env);
    }
    return (0);
}