#include "minishell.h"

int		if_has_dollar(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == '$')
			return(1);
		i++;
	}
	return(0);
}

char	*take_env(char *str, int i)
{
	char *tmp;
	int j;
	j = ft_strlen(str);
	tmp = malloc(sizeof(char) * j);
	j = 0;
	i += 1;
	while(str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	tmp = getenv(tmp);
	if(tmp == NULL)
		return(ft_strdup(""));
	return(tmp);
}

int		pass_env(char *str, int i)
{
	i += 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '$')
		i++;
	return (i);
}

char	*exp_dollar(char *str, int quote)
{
	int i = 0;
	char *tmp;
	int j = 0;
	char *res;
	//int len = 0;

	//len = ft_strlen(str);
	tmp = malloc(sizeof(char) * 10000);
	i = 0;
	if(str[i] == '$' && str[i + 1] == '?')
		return(str);
	if(str[i] == '$' && str[i + 1] == '$')
		return(str);
	if(if_has_dollar(str) == 0 || quote == 1)
		return(str);
	else
	{
		while(str[i])
		{
			if(str[i] == '$')
			{
				res = take_env(str, i);
				tmp = ft_strjoin(tmp, res);
				j += ft_strlen(res);
				i = pass_env(str, i);
			}
			else
			{
				tmp[j] = str[i];
				i++;
				j++;
			}
		}
		tmp[j] = '\0';
	}
	return(tmp);
}