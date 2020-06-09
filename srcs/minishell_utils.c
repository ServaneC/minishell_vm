/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 16:11:37 by schene            #+#    #+#             */
/*   Updated: 2020/06/09 15:23:28 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_tmp(char *cmd)
{
	char	*tmp;
	int		i;
	int		j;
	char	c;

	i = -1;
	j = -1;
	tmp = ft_strdup("\0");
	while (cmd[++i])
	{
		if ((cmd[i] == '\'' || cmd[i] == '\"') && is_meta(cmd, i))
		{
			if (cmd[i + 1] && cmd[i + 1] == cmd[i] && is_meta(cmd, i + 1))
				tmp = clean_ft_strjoin(tmp, ft_strdup("\"\""));
			c = cmd[i];
			while (cmd[++i])
			{
				if (cmd[i] == c)
					break ;
				if (cmd[i])
				{
					if (cmd[i] == '\\' && cmd[i + 1] && cmd[i + 1] == '\"')
						i++;
					else if (cmd[i] == '\\' && ((cmd[i + 1] && cmd[i + 1] != '$') || !cmd[i + 1]))
						tmp = clean_ft_strjoin(tmp, ft_strdup("\\"));
					tmp = clean_ft_strjoin(tmp, ft_substr(cmd, i, 1));
					if (cmd[i + 1] && cmd[i + 1] == '\\' && cmd[i + 2] && cmd[i + 2]== '\"')
						i++;
				}
				else if (cmd[++i])
					tmp = clean_ft_strjoin(tmp, ft_substr(cmd, i, 1));
			}
		}
		else if (cmd[i])
		{
			if (cmd[i] != '\\')
				tmp = clean_ft_strjoin(tmp, ft_substr(cmd, i, 1));
			else if (cmd[i + 1] && (cmd[i + 1] == '\\' || cmd[i + 1] == '$'))
			{
				tmp = clean_ft_strjoin(tmp, ft_substr(cmd, i, 2));
				i++;
			}
			else if (cmd[++i])
				tmp = clean_ft_strjoin(tmp, ft_substr(cmd, i, 1));
			else
				tmp = clean_ft_strjoin(tmp, ft_strdup(" "));
		}
		if (!cmd[i])
			break ;
	}
	return (tmp);
}

char		*remove_quotes(char *cmd)
{
	char *tmp;

	tmp = get_tmp(cmd);
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
