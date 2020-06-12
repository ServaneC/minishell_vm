/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:22:06 by schene            #+#    #+#             */
/*   Updated: 2020/06/12 18:16:09 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*rm_quote_value(char *str)
{
	int		i;
	char	c;
	char	 *ret;

	ret = ft_strdup("\0");
	i = -1;
	while (str[++i])
	{
		if (is_quotes(str, i))
		{
			c = str[i];
			i++;;
			while (str[i] != c)
				ret = clean_ft_strjoin(ret, ft_substr(str, i, 1));
		}
		else
			ret = clean_ft_strjoin(ret, ft_substr(str, i, 1));
		if (!str[i])
			break ;
	}
	free(str);
	str = NULL;
	return (ret);
}

char	*rm_quotes_env(char *var)
{
	char	*name;
	char	*value;
	char	*ret;
	int		len;

	ret = ft_strdup(var);
	var = remove_quotes(var);
	len = ft_strncmp(ret, var, ft_strlen(var));
	free(ret);
	ret = NULL;
	if (len == 0)
	{
		len = ft_strlen(var) - ft_strlen(ft_strchr(var, '='));
		name = ft_substr(var, 0, ++len);
		value = ft_strdup(&var[len]);
		value = rm_quote_value(value);
		ret = ft_strjoin(name, value);
		free(value);
		free(var);
		free(name);
		return (ret);
	}
	return (var);
}

char	*removeplus(char *str)
{
	char	*start;
	char	*end;

	end = ft_strchr(str, '+');
	if (end == NULL)
		return (str);
	end = ft_substr(end, 1, ft_strlen(end - 1));
	start = ft_substr(str, 0, ft_strlen(str) - ft_strlen(end) - 1);
	free(str);
	str = ft_strjoin(start, end);
	free(start);
	free(end);
	return (str);
}
