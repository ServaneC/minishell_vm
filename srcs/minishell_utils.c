/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 16:11:37 by schene            #+#    #+#             */
/*   Updated: 2020/06/05 17:10:46 by schene           ###   ########.fr       */
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
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i];
			while (cmd[++i])
			{
				if (cmd[i] == c)
					break ;
				tmp[++j] = cmd[i];
			}
		}
		else
			tmp[++j] = cmd[i];
	}
	tmp[++j] = '\0';
	return (tmp);
}

char		*remove_quotes(char *cmd)
{
	char *tmp;

	if (!(tmp = malloc(sizeof(char) * ft_strlen(cmd) + 1)))
		return (NULL);
	get_tmp(cmd, tmp);
	free(cmd);
	return (tmp);
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
