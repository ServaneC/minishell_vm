/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 15:59:51 by schene            #+#    #+#             */
/*   Updated: 2020/06/06 16:03:46 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static int	word_count(char *str, const char *charset)
{
	int		i;
	int		nbwords;
	char	c;

	i = -1;
	nbwords = 0;
	while (str[++i])
	{
		if (i == 0 || (i > 0 &&
			(!(is_sep(str[i], charset)) && is_sep(str[i - 1], charset))))
			nbwords++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			while (str[++i] && str[i] != c)
				;
		}
		if (!str[i])
			break ;
	}
	return (nbwords);
}

static int	w_len(char *s, int i, const char *charset)
{
	int		len;
	char	c2;

	len = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c2 = s[i];
			while (s[++i] && s[i] != c2)
				len++;
			if (!s[i])
				return (len + 1);
			len += 2;
		}
		else if (!is_sep(s[i], charset))
			len++;
		else if (i > 0 && !is_sep(s[i - 1], charset))
			return (len);
		i++;
	}
	return (len);
}

static int	fill_sp_tab(char **tab, char *tmp, char const *charset)
{
	int		len;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	while (++j < word_count(tmp, charset) && tmp[i])
	{
		while (is_sep(tmp[i], charset))
			i++;
		len = w_len(tmp, i, charset);
		if (!(tab[j] = (char *)malloc(sizeof(char) * len + 1)))
			return (0);
		k = 0;
		while (tmp[i] && k < len)
			tab[j][k++] = tmp[i++];
		tab[j][k] = '\0';
		if (tmp[i] && is_sep(tmp[i], charset))
			i++;
	}
	tab[j] = 0;
	return (1);
}

char		**split_spaces(char *s, char const *charset)
{
	char	**tab;

	if (!s)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) *
		(word_count(s, charset) + 1))))
		return (NULL);
	if (fill_sp_tab(tab, s, charset) == 0)
		return (NULL);
	return (tab);
}
