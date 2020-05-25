/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 15:59:51 by schene            #+#    #+#             */
/*   Updated: 2020/05/25 16:56:29 by schene           ###   ########.fr       */
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

static int	is_word(char c, char cbefore, const char *charset)
{
	return (!(is_sep(c, charset)) && is_sep(cbefore, charset));
}

static int	word_count(char *str, const char *charset)
{
	int		i;
	int		nbwords;
	char	c;

	i = 0;
	nbwords = 0;
	while (str[i])
	{
		if ((!is_sep(str[i], charset) && i == 0) ||
			(is_word(str[i], str[i - 1], charset)))
			nbwords++;
		else if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
		i++;
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
			len += 2;
		}
		else if (!is_sep(s[i], charset))
			len++;
		else if (i > 0 && !is_sep(s[i-1], charset))
			return (len);
		i++;
	}
	return (len);
}

char		**split_spaces(char *s, char const *charset)
{
	char	**tab;
	char	*tmp;
	int		len;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	tmp = ft_strtrim(s, " \t\n");
	if (!(tab = (char **)malloc(sizeof(char *) * (word_count(tmp, charset) + 1))))
		return (NULL);
	i = 0;
	j = -1;
	while (++j < word_count(tmp, charset) && tmp[i])
	{
		len = w_len(tmp, i, charset);
		if (!(tab[j] = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
		k = 0;
		while (tmp[i] && k < len)
			tab[j][k++] = tmp[i++];
		tab[j][k] = 0;
		if (s[i] && is_sep(s[i], charset))
			i++;
	}
	tab[j] = 0;
	free(tmp);
	return (tab);
}