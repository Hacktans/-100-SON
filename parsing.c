#include "minishell.h"

int cmd_chk(char *cmd, char **paths) 
{
	if (!cmd || !paths) return 0;

	int i = 0;
	while (paths[i])
	{
		char *path = ft_strjoin(paths[i], "/");
		char *full_path = ft_strjoin(path, cmd);
		free(path);

		if (access(full_path, X_OK) == 0) 
		{
			free(full_path);
			return 1;
		}
		free(full_path);
		i++;
	}
	return 0;
}

void add_cmds(t_cmd *cmds, char *value, int index) {
	if (!cmds || !value) return;
	
	char **new_command = malloc(sizeof(char *) * (index + 2));  // +2 (index+1 + NULL)
	
	if (cmds->command) {
		for (int i = 0; i < index; i++) {
			new_command[i] = cmds->command[i];
		}
		free(cmds->command);  // Eski diziyi temizle
	}
	
	new_command[index] = ft_strdup(value);
	new_command[index + 1] = NULL;  // NULL terminator
	
	cmds->command = new_command;  // Yeni diziyi ata
}

void    rdr_parser(t_cmd *cmd, t_token *tokens, int i)
{
	char *tmp;
	cmd->redirections = (char **)malloc(sizeof (char *) * (cmd->rdr_c + 1));
	cmd->redirections[cmd->rdr_c] = NULL;
	tmp = ft_strjoin(tokens->value, " ");
	tmp = ft_strjoin(tmp , tokens->next->value);
	cmd->redirections[i] = tmp;
	i++;
}

t_cmd *ft_parsing(t_token *tokens, t_list *mini) 
{
	if (!tokens || !mini) return NULL;

	t_cmd *cmds = ft_calloc(1, sizeof(t_cmd));
	int pipe_c = 0, rdr_c = 0, word_count = 0;

	t_token *tmp = tokens;
	while (tmp) 
	{
		if (strncmp(tmp->type, "word", 4) == 0)
			word_count++;
		else if (strncmp(tmp->type, "pipe", 4) == 0)
			pipe_c++;
		else if (strncmp(tmp->type, "rdr", 3) == 0)
			rdr_c++;
		tmp = tmp->next;
	}
	cmds->pipe_c = pipe_c;
	cmds ->rdr_c = rdr_c;
	int flag;
	flag = 0;
	if (word_count > 0 && strncmp(tokens->type, "word", 4) == 0) 
	{
		if (ft_strncmp(tokens->value, "cd", 2) == 0)
			flag = 1;
		if (ft_strcmp(tokens->value, "export") == 0)
			flag = 1;
		if (ft_strcmp(tokens->value, "unset") == 0)
			flag = 1;
		if (!cmd_chk(tokens->value, mini->paths) && flag == 0) 
		{
			printf("BÖYLE BİR KOMUT YOK\n");
			return(NULL);
		}
	}
	tmp = tokens;
	int index = 0;
	int rdr_l = 0;
	while (tmp)
	{
		if (strncmp(tmp->type, "word", 4) == 0)
			add_cmds(cmds, tmp->value, index++);
		if (strncmp(tmp ->type, "rdr", 3) == 0)
		{
			rdr_parser(cmds, tmp, rdr_l);
			rdr_l++;
		}
		tmp = tmp->next;
	}

	return cmds;
}
