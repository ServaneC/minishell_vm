/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:02:24 by schene            #+#    #+#             */
/*   Updated: 2020/06/05 18:16:16 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char			*rm_quotes_env(char *var)
{
	char	*name;
	char	*value;
	char	*ret;
	int		len;

	ret = ft_strdup(var);
	var = remove_quotes(var);
	len = ft_strncmp(ret, var, ft_strlen(var));
	free(ret);
	if (len == 0)
	{
		len = ft_strlen(var) - ft_strlen(ft_strchr(var, '='));
		name = ft_substr(var, 0, ++len);
		value = ft_strdup(&var[len]);
		value = remove_quotes(value);
		ret = ft_strjoin(name, value);
		free(value);
		free(var);
		free(name);
		return (ret);
	}
	return (var);
}

static int		count_quotes(char *str, char c)
{
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	while (str[++i])
		if (str[i] == c)
			nb++;
	return (nb);
}

static char		*new_strquote(char *str, char c)
{
	char	*start;
	int		len;
	char	*ret;
	char	*ptr;

	ptr = ft_strrchr(str, c);
	len = ft_strlen(str) - ft_strlen(ptr);
	start = ft_substr(str, 0, len);
	ret = ft_strjoin(start, ptr + 1);
	free(start);
	free(str);
	return (ret);
}

char			*rm_sgl_quote(char *str)
{
	char	q;

	q = '\"';
	if (ft_strchr(str, q))
		if (count_quotes(str, q) % 2)
			str = new_strquote(str, q);
	q = '\'';
	if (ft_strchr(str, q))
		if (count_quotes(str, q) % 2)
			str = new_strquote(str, q);
	return (str);
}
