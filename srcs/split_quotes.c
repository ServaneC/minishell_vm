/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 11:43:41 by schene            #+#    #+#             */
/*   Updated: 2020/06/08 17:15:15 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		else_nb_w(char *str, int i)
{
	i--;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i--;
			break ;
		}
	}
	return (i);
}

static int		nb_word(char *str)
{
	int		count;
	int		i;
	char	c;

	i = -1;
	count = 0;
	while (str[++i])
	{
		count++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			while (str[++i])
				if (str[i] == c)
					break ;
			if (!str[i] && count > 1)
				return(count -1);
		}
		else
			i = else_nb_w(str, i);
		if (!str[i])
			break ;
	}
	return (count);
}

static int		w_len(char *str, int i)
{
	int		len;
	char	c;

	len = 0;
	i--;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			while (str[++i] != c && str[i])
				len++;
			if (!str[i])
				return(len + 1);
			return (len + 2);
		}
		else if (str[i])
			len++;
		if (!str[i])
			return(len);
	}
	return (len);
}

static int		fill_tab_q(int nb_line, char **tab, char *str)
{
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	j = -1;
	while (++j < nb_line && str[i])
	{
		len = w_len(str, i);
		if (!(tab[j] = (char *)malloc(sizeof(char) * (len + 1))))
			return (0);
		k = 0;
		while (str[i] && k < len)
			tab[j][k++] = str[i++];
		tab[j][k] = '\0';
	}
	tab[j] = 0;
	return (1);
}

char			**tab_of_quotes(char *str)
{
	char	**tab;
	int		nb_line;

	if (!str)
		return (NULL);
	nb_line = nb_word(str);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_line + 1))))
		return (NULL);
	if (fill_tab_q(nb_line, tab, str) == 0)
		return (NULL);
	return (tab);
}
