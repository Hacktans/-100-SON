#include "minishell.h"

void    add_token(t_token **tokens, char *value, char *type)
{
	t_token *new_node;
	t_token *tmp;
	new_node = malloc(sizeof(t_token));
	if(!new_node)
		return ;
	new_node->type = ft_strdup(type);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if(*tokens == NULL)
		*tokens = new_node;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void 	write_list(t_token *token)
{
	t_token *tmp = token;
	while(tmp)
	{
		printf("Eleman : %s\n", tmp->value);
		tmp = tmp->next;
	}
}

int 	syntax_chk(t_token *tokens, char *input)
{
	t_token *tmp = tokens;
	if(ft_strncmp(tmp->type,"pipe", 4) == 0)
		return(0);
	if(ft_strncmp(tmp->type,"rdr", 3) == 0)
		return(0);
	if(!ft_quote_chk(input))
		return(0);
	return(1);
}

void ft_token(char *input, t_token **tokens)
{
    int i = 0;
    int len = 0;
    char word[1024];

	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(tokens, ">>", "rdr");
			i += 2;
		}
		else if (input[i] == '<' && input[i + 1] == '<') 
		{
			add_token(tokens, "<<", "rdr");
			i += 2;
		}
		else if (input[i] == '|')
		{
			add_token(tokens, "|", "pipe");
			i++;
		}
		else if (input[i] == '>')
		{
			add_token(tokens, ">", "rdr");
			i++;
		}
		else if (input[i] == '<')
		{
			add_token(tokens, "<", "rdr");
			i++;
		}
		else
		{
			len = 0;
			while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '<' && input[i] != '>')
			{
				if (input[i] == '\'')
				{
					i++; 
					while (input[i] && input[i] != '\'' && input[i] != '\\')  //tek tırnaklı argümanlar ve komutlar
					{
						word[len] = input[i];
						len++;
						i++;
					}
					if (input[i] == '\'')
						i++;
				}
				else if(input[i] == '"')
				{
					i++;
					while(input[i] && input[i] != '"' && input[i] != '\\')
					{
						word[len] = input[i];
						len++;
						i++;
					}
					if(input[i] == '"')
						i++;
				}
				else if(input[i] == '\\' && char_is_esc(input[i + 1]))
				{
					word[len] = input[i + 1];
					len++;
					i += 2;
				}
				else
				{
					word[len] = input[i];
					len++;
					i++;
				}
			}
			word[len] = '\0';
			add_token(tokens, word, "word");
		}
	}
	write_list(*tokens);
}

void reset_tokens(t_token *tokens)
{
    t_token *tmp;
    while (tokens)
    {
        tmp = tokens->next;
        free(tokens->value);
        free(tokens->type);
        free(tokens);
        tokens = tmp;
    }
}