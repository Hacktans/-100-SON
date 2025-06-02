#include "minishell.h"

void    ft_echo(char **strngs)
{
    int i = 1;
    int j = 0;

    while(strngs[i])
    {
        j = 0;
        while(strngs[i][j])
        {
            write(1, &strngs[i][j], 1);
            j++;
        }
        if (strngs[i + 1] && strngs[i][0] != '\0')
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
}