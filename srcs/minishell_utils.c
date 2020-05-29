/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 16:11:37 by schene            #+#    #+#             */
/*   Updated: 2020/05/29 17:49:19 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*remove_quotes(char *cmd)
{
	int		i;
	int		j;
	char	c;
	char	*tmp;

	i = -1;
	j = -1;
	if (!(tmp = malloc(sizeof(char) * ft_strlen(cmd) + 1)))
		return (NULL);
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
	free(cmd);
	printf("[%s]\n", tmp);
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
