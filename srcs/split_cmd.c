/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 16:16:32 by schene            #+#    #+#             */
/*   Updated: 2020/06/05 14:46:01 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	word_count(char *s)
{
	int		i;
	char	c2;
	int		count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		while (s[i] && s[i] == ';')
			i++;
		if ((s[i] != ';' && i == 0) || (s[i] != ';' && s[i - 1] == ';'))
			count++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			c2 = s[i];
			i++;
			while (s[i] != c2 && s[i])
				i++;
		}
	}
	return (count);
}

static int	w_len(char *s, int i)
{
	int		len;
	char	c2;

	len = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c2 = s[i];
			while (s[++i] != c2 && s[i])
				len++;
			len += 2;
		}
		else if (s[i] != ';')
			len++;
		else if (i > 0 && s[i - 1] != ';')
			return (len);
		i++;
	}
	return (len);
}

static int	parse_error(char *s)
{
	char	c;
	int		i;
	char	*ptr;
	char	*ptr2;

	ptr = ft_strchr(s, '\"');
	ptr2 = ft_strchr(s, '\'');
	c = '\'';
	if ((ptr == NULL && ptr2) || ft_strlen(ptr2) > ft_strlen(ptr))
		ptr = ptr2;
	else if ((ptr && ptr2 == NULL) || ft_strlen(ptr2) < ft_strlen(ptr))
		c = '\"';
	if (ptr == NULL)
	{
		if (ft_strnstr(s, ";;", ft_strlen(s)))
			return (1);
		else
			return (0);
	}
	if (ft_strnstr(s, ";;", ft_strlen(s) - ft_strlen(ptr)))
		return (1);
	i = 1;
	while (ptr[i] && ptr[i] != c)
		i++;
	return (parse_error(&ptr[i + 1]));
}

static int	fill_cmd(char **tab, char *tmp)
{
	int i;
	int j;
	int k;
	int len;

	i = 0;
	j = -1;
	while (++j < word_count(tmp) && tmp[i])
	{
		len = w_len(tmp, i);
		if (!(tab[j] = (char *)malloc(sizeof(char) * (len + 1))))
			return (0);
		k = 0;
		while (tmp[i] && k < len)
			tab[j][k++] = tmp[i++];
		tab[j][k] = 0;
		if (tmp[i] && tmp[i] == ';')
			i++;
	}
	tab[j] = 0;
	return (1);
}

char		**split_quotes(char *s, t_data *data)
{
	char	**tab;
	char	*tmp;

	if (!s)
		return (NULL);
	if (parse_error(s))
	{
		data->status = 2;
		ft_putendl_fd("parse error near `;;'", 2);
		return (NULL);
	}
	tmp = ft_strtrim(s, " ;");
	if (!(tab = (char **)malloc(sizeof(char *) * (word_count(tmp) + 1))))
		return (NULL);
	if (fill_cmd(tab, tmp) == 0)
		return (NULL);
	free(tmp);
	return (tab);
}
