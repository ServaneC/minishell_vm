/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 14:37:25 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 15:45:07 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		echo_variable(char *s, t_data *data, char **ret, int i)
{
	char	*tmp;

	if (s[i + 1] == '?')
	{
		*ret = clean_ft_strjoin(*ret, ft_itoa(data->status));
		i += 1;
	}
	else
	{
		if (var_value(data->env, &s[i]) != NULL)
		{
			tmp = ft_strjoin(*ret, var_value(data->env, &s[i]));
			free(*ret);
			*ret = tmp;
		}
		while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_'))
			;
		i--;
	}
	return (i);
}

static char		*echo_str_sgl(char *str)
{
	int		i;
	char	*ret;
	char	*s;

	i = -1;
	ret = ft_strdup("\0");
	s = ft_strtrim(str, "\'");
	while (s[++i])
	{
		ret = clean_ft_strjoin(ret, ft_substr(s, i, 1));
		if (!s[i])
			break ;
	}
	free(s);
	return (ret);
}

static char		*get_s(char *str, int m)
{
	char	*s;

	if (str[0] != '\'')
	{
		s = ft_strtrim(str, "\"");
		if (m && s[0] == '\0')
		{
			free(s);
			s = ft_strdup(" ");
		}
		return (s);
	}
	return (NULL);
}

char			*echo_str(char *str, t_data *data, int m)
{
	int		i;
	char	*ret;
	char	*s;

	i = -1;
	ret = ft_strdup("\0");
	if (!str[0])
		return (ret);
	if ((s = get_s(str, m)) != NULL)
	{
		while (s[++i])
		{
			if (s[i] == '$' && s[i + 1] && (ft_isalnum(s[i + 1])
				|| s[i + 1] == '?'))
				i = echo_variable(s, data, &ret, i);
			else
				ret = clean_ft_strjoin(ret, ft_substr(s, i, 1));
			if (!s[i])
				break ;
		}
		free(s);
	}
	else
		ret = clean_ft_strjoin(ret, echo_str_sgl(str));
	return (ret);
}
