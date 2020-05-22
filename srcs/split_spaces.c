/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 15:59:51 by schene            #+#    #+#             */
/*   Updated: 2020/05/22 16:09:00 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**free_mallocs(char **buffer, int *size)
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
	return (NULL);
}

static int	is_sep(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		++i;
	}
	return (0);
}

static int	is_word(char c, char cbefore, const char *charset)
{
	return (!(is_sep(c, charset)) && is_sep(cbefore, charset));
}

static int	ft_nbwords(const char *str, const char *charset)
{
	int		i;
	int		nbwords;
	char	c;

	i = 0;
	nbwords = 0;
	while (str[i])
	{
		if (is_word(str[i], str[i - 1], charset) ||
				(!is_sep(str[i], charset) && i == 0))
			nbwords++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		i++;
	}
	return (nbwords);
}

static int	*ft_size(const char *str, const char *charset)
{
	int		i;
	int		j;
	char	c;
	int		nbwords;
	int		*size;

	i = 0;
	nbwords = ft_nbwords(str, charset);
	if (!(size = malloc(sizeof(int) * nbwords)))
		return (0);
	while (i <= nbwords)
	{
		size[i] = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			while (str[++i] != c && str[i])
				size[j]++;
			size[j] += 2;
		}
		else if (!(is_sep(str[i], charset)))
			size[j]++;
		else if (i > 0 && !is_sep(str[i - 1], charset))
			j++;
		i++;
	}
	return (size);
}

char		**split_spaces(char *s, char *charset)
{
	char	**tab;
	int		i;
	int		len;
	int		nb_word;
	int		*size;

	s = ft_strtrim(s, charset);
	nb_word = ft_nbwords(s, charset);
	if (!(tab = malloc(sizeof(char *) * (nb_word + 1))))
		return (NULL);
	size = ft_size(s, charset);
	i = -1;
	len = 0;
	while (size[++i])
	{
		if (!(tab[i] = malloc(sizeof(char) * (size[i] + 1))))
			return (free_mallocs(tab, size));
		tab[i] = ft_substr(s, len, size[i]);
		len += size[i] + 1;
		tab[i + 1] = NULL;
	}
	free(size);
	size = NULL;
	return (tab);
}
