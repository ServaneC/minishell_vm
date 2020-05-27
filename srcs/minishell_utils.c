/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 16:11:37 by schene            #+#    #+#             */
/*   Updated: 2020/05/27 16:17:32 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*remove_quotes(char *cmd)
{
	char *tmp;

	if (cmd[0] == '\'')
		tmp = ft_strtrim(cmd, "\' ");
	else if (cmd[0] == '\"')
		tmp = ft_strtrim(cmd, "\" ");
	else
		tmp = ft_strtrim(cmd, " \t\n");
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
