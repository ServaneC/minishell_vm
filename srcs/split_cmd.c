/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 16:16:32 by schene            #+#    #+#             */
/*   Updated: 2020/06/11 12:44:39 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	word_count(char *s, char sep)
{
	int		i;
	char	c2;
	int		count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		while (s[i] && s[i] == sep)
			i++;
		if ((s[i] != sep && i == 0) || (s[i] != sep && s[i - 1] == sep))
			count++;
		if ((s[i] == '\'' || s[i] == '\"') && is_meta(s, i))
		{
			c2 = s[i];
			while (s[++i])
			{
				if (s[i] == c2 && is_meta(s, i))
					break ;
			}
		}
		if (!s[i])
			break ;
	}
	return (count);
}

static int	w_len(char *s, int i, int len, char sep)
{
	char	c2;

	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && is_meta(s, i))
		{
			c2 = s[i];
			while (s[++i])
			{
				if (s[i] == c2 && is_meta(s, i))
					break ;
				len++;
			}
			if (!s[i])
				return (len + 1);
			len += 2;
		}
		else if (s[i] != sep)
			len++;
		else if (i > 0 && s[i - 1] != sep)
			return (len);
		i++;
	}
	return (len);
}

static int	fill_cmd(char **tab, char *tmp, char sep)
{
	int i;
	int j;
	int k;
	int len;

	i = 0;
	j = -1;
	while (++j < word_count(tmp, sep) && tmp[i])
	{
		len = w_len(tmp, i, 0, sep);
		if (!(tab[j] = (char *)malloc(sizeof(char) * (len + 1))))
			return (0);
		k = 0;
		while (tmp[i] && k < len)
			tab[j][k++] = tmp[i++];
		tab[j][k] = 0;
		if (tmp[i] && tmp[i + 1])
			i++;
	}
	tab[j] = 0;
	return (1);
}

char		**split_quotes(char *s, t_data *data, char sep)
{
	char	**tab;

	if (!s)
		return (NULL);
	if (parse_error(s))
	{
		data->status = 2;
		return (NULL);
	}
	if (!(tab = (char **)malloc(sizeof(char *) * (word_count(s, sep) + 1))))
		return (NULL);
	if (fill_cmd(tab, s, sep) == 0)
		return (NULL);
	return (tab);
}
