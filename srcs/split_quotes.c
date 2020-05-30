/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 11:43:41 by schene            #+#    #+#             */
/*   Updated: 2020/05/30 14:39:53 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		//printf("str[%d] = %c\n", i, str[i]);
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			while (str[++i])
			{
				if (str[i] == c)
					break ;
			}
		}
		else
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
		}
		if (!str[i])
			break ;
	}
	//printf("count = %d\n", count);
	return (count);
}

static int	w_len(char *str, int i)
{
	int 	len;
	char 	c;

	len = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		c = str[i];
		while (str[++i] != c && str[i])
			len++;
		return (len + 2);
	}
	while (str[i] && (str[i] != '\'' && str[i] != '\"'))
	{
		i++;
		len++;
	}
	return(len);
}

char		**tab_of_quotes(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	int		len;
	int		nb_line;

	if (!str)
		return (NULL);
	//printf("str = [%s]\n", str);
	nb_line = nb_word(str);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_line + 1))))
		return (NULL);
	i = 0;
	j = -1;
	while (++j < nb_line && str[i])
	{
		len = w_len(str, i);
		if (!(tab[j] = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		k = 0;
		while (str[i] && k < len)
			tab[j][k++] = str[i++];
		tab[j][k] = '\0';
	}
	tab[j] = 0;
	return (tab);
}