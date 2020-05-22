/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 16:16:32 by schene            #+#    #+#             */
/*   Updated: 2020/05/22 16:08:18 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	free_mallocs(char **buffer, int *size)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
	free(size);
	return (0);
}

static int	ft_nbword(char const *s)
{
	int		i;
	char	c;
	int		nbword;

	i = 0;
	nbword = 0;
	while (s[i])
	{
		if ((s[i] != ';' && s[i - 1] == ';') || (s[i] != ';' && i == 0))
			nbword++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			i++;
			while (s[i] != c && s[i])
				i++;
		}
		i++;
	}
	return (nbword);
}

static int	*fill_tab_size(char const *s)
{
	int		i;
	int		j;
	char	c;
	int		*size;
	int		nbword;

	i = -1;
	nbword = ft_nbword(s);
	if (!(size = malloc(sizeof(int) * nbword)))
		return (NULL);
	while (++i <= nbword)
		size[i] = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			while (s[++i] != c && s[i])
				size[j]++;
			size[j] += 2;
		}
		else if (s[i] != ';')
			size[j]++;
		else if (i > 0 && s[i - 1] != ';')
			j++;
		i++;
	}
	return (size);
}

static int	create_tab(char const *s, char **tab, int *size)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (size[i])
	{
		if (!(tab[i] = malloc(sizeof(char) * (size[i] + 1))))
			return (free_mallocs(tab, size));
		tab[i] = ft_substr((char *)s, len, size[i]);
		len += size[i] + 1;
		i++;
	}
	return (1);
}

char		**split_quotes(char const *s)
{
	char	**tab;
	int		*size;
	int		nb_word;

	s = ft_strtrim((char *)s, "; ");
	nb_word = ft_nbword(s);
	if (!(tab = malloc(sizeof(char *) * (nb_word + 1))))
		return (NULL);
	size = fill_tab_size(s);
	if (!create_tab(s, tab, size))
		return (NULL);
	free(size);
	tab[nb_word] = 0;
	return (tab);
}
