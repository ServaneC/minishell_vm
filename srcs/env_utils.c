/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:22:06 by schene            #+#    #+#             */
/*   Updated: 2020/06/15 15:57:38 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*rm_quote_value(char *str)
{
	int		i;
	char	c;
	char	*ret;

	ret = ft_strdup("\0");
	i = -1;
	while (str[++i])
	{
		if (is_quotes(str, i))
		{
			c = str[i];
			i++;
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

int		len_variable(void *str)
{
	int		len;
	char	*s;

	s = (char *)str;
	len = 0;
	while (ft_isalnum(s[len]) || s[len] == '_')
		len++;
	if (s[len] == '+')
		len++;
	return (len);
}

char	**convert_env_to_tab(t_list *env)
{
	char	**tab;
	int		i;
	int		len;

	len = ft_lstsize(env);
	if (!(tab = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len && env)
	{
		tab[i] = env->content;
		tab[i + 1] = NULL;
		env = env->next;
	}
	return (tab);
}
