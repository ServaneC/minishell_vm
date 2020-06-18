/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 16:11:37 by schene            #+#    #+#             */
/*   Updated: 2020/06/18 15:01:26 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int			is_meta(char *str, int i)
{
	if (i == 0)
		return (1);
	if (str[i - 1] && str[i - 1] == '\\')
		return (str[i - 2] && str[i - 2] == '\\');
	return (str[i - 1] && str[i - 1] != '\\');
}
