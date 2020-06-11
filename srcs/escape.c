/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 11:19:54 by schene            #+#    #+#             */
/*   Updated: 2020/06/11 14:39:17 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			is_meta(char *str, int i)
{
	if (i == 0)
		return (1);
	if (str[i - 1] && str[i - 1] == '\\')
		return (str[i - 2] && str[i - 2] == '\\');
	return (str[i - 1] && str[i - 1] != '\\');
}

static int	tmp_is_quote(int i, char **tmp, char *cmd)
{
	char	c;

	if (cmd[i + 1] && cmd[i + 1] == cmd[i] && is_meta(cmd, i + 1))
		*tmp = clean_ft_strjoin(*tmp, ft_strdup("\"\""));
	c = cmd[i];
	while (cmd[++i])
	{
		if (cmd[i] == c)
			break ;
		if (cmd[i])
		{
			if (cmd[i] == '\\' && cmd[i + 1] && cmd[i + 1] == '\"')
				i++;
			else if (cmd[i] == '\\' && ((cmd[i + 1] && cmd[i + 1] != '$'
				&& cmd[i + 1] != '\\') || !cmd[i + 1]))
				*tmp = clean_ft_strjoin(*tmp, ft_strdup("\\"));
			*tmp = clean_ft_strjoin(*tmp, ft_substr(cmd, i, 1));
			if (cmd[i + 1] &&
				cmd[i + 1] == '\\' && cmd[i + 2] && cmd[i + 2] == '\"')
				*tmp = clean_ft_strjoin(*tmp, ft_substr(cmd, ++i, 1));
		}
		else if (cmd[++i])
			*tmp = clean_ft_strjoin(*tmp, ft_substr(cmd, i, 1));
	}
	return (i);
}

static int	tmp_not_quotes(int i, char **tmp, char *cmd)
{
	if (cmd[i] != '\\')
		*tmp = clean_ft_strjoin(*tmp, ft_substr(cmd, i, 1));
	else if ((cmd[i - 1] && cmd[i - 1] == '$') ||
		(cmd[i + 1] && (cmd[i + 1] == '\\' || cmd[i + 1] == '$')))
	{
		*tmp = clean_ft_strjoin(*tmp, ft_substr(cmd, i, 2));
		i++;
	}
	else if (cmd[++i])
		*tmp = clean_ft_strjoin(*tmp, ft_substr(cmd, i, 1));
	else
		*tmp = clean_ft_strjoin(*tmp, ft_strdup(" "));
	return (i);
}

static char	*cut_escape_quote(char *cmd)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strdup("\0");
	while (cmd[++i])
	{
		if (is_quotes(cmd, i))
			i = tmp_is_quote(i, &tmp, cmd);
		else if (cmd[i])
			i = tmp_not_quotes(i, &tmp, cmd);
		if (!cmd[i])
			break ;
	}
	return (tmp);
}

char		*remove_quotes(char *cmd)
{
	char *tmp;

	tmp = cut_escape_quote(cmd);
	free(cmd);
	cmd = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (cmd);
}
