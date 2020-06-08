/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 16:11:37 by schene            #+#    #+#             */
/*   Updated: 2020/06/08 17:22:56 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_tmp(char *cmd, char *tmp)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	j = -1;
	//printf("-[%s]\n", cmd);
	while (cmd[++i])
	{
		//printf("(%s)\n", &cmd[i]);
		if ((cmd[i] == '\'' || cmd[i] == '\"'))
		{
			if (cmd[i+1] && cmd[i + 1] == cmd[i])
			{
				tmp[++j] = '\"';
				tmp[++j] = '\"';
			}
			c = cmd[i];
			while (cmd[++i])
			{
				if (cmd[i] == c /*&& cmd[i - 1] != '\\'*/)
					break ;
				if (cmd[i] == '\\' && cmd[i + 1] && cmd[i + 1] == '$')
					tmp[++j] = cmd[i];
				else if (cmd[i])
				{
					if (cmd[i] == '\\')
					{
						if (cmd[i + 1] && cmd[i + 1] == '\"')
							i++;
						else
							tmp[++j] = '\\';
					}
					if (cmd[i])
						tmp[++j] = cmd[i];
				}
				else if (cmd[++i])
					tmp[++j] = cmd[i];
			}
		}
		else if (cmd[i])
		{
			if (cmd[i] != '\\')
				tmp[++j] = cmd[i];
			else if (cmd[i + 1] && (cmd[i + 1] == '\\' || cmd[i + 1] == '$'))
			{
				tmp[++j] = cmd[i];
				tmp[++j] = cmd[++i];
			}
			else if (cmd[++i])
				tmp[++j] = cmd[i];
			else
				tmp[++j] = ' ';
		}
		if (!cmd[i])
			break ;
	}
	tmp[++j] = '\0';
	//printf("->[%s]\n", tmp);
	return (tmp);
}

char		*remove_quotes(char *cmd)
{
	char *tmp;

	if (!(tmp = malloc(sizeof(char) * ft_strlen(cmd) + 10)))
		return (NULL);
	get_tmp(cmd, tmp);
	free(cmd);
	cmd = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (cmd);
}

void		ft_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

char		*clean_ft_strjoin(char *s1, char *s2)
{
	char *ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	s1 = ret;
	return (s1);
}

char		*var_value(t_list *env, char *var)
{
	char	*name;
	int		len;
	int		len2;

	name = &var[1];
	len2 = 0;
	while (ft_isalnum(name[len2]) || name[len2] == '_')
		len2++;
	while (env)
	{
		len = (ft_strlen(env->content) -
			ft_strlen(ft_strchr(env->content, '=')));
		len = len2 > len ? len2 : len;
		if (ft_strncmp(env->content, name, len) == 0)
			return (ft_strchr(env->content, '=') + 1);
		env = env->next;
	}
	if (ft_isdigit(name[0]) && name[1])
		return (&name[1]);
	return (NULL);
}
