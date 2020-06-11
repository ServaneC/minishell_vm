/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 14:37:25 by schene            #+#    #+#             */
/*   Updated: 2020/06/11 13:58:31 by schene           ###   ########.fr       */
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

static char		*get_s(char *str, t_data *data)
{
	char	*s;
	char	*ret;
	int		i;

	if (str[0] != '\'')
	{
		ret = ft_strdup("\0");
		s = remove_quotes(ft_strdup(str));
		i = -1;
		while (s[++i])
		{
			if (s[i] == '\\')
				ret = clean_ft_strjoin(ret, ft_substr(s, ++i, 1));
			else if (s[i] == '$' && s[i + 1] &&
				(ft_isalnum(s[i + 1]) || s[i + 1] == '?'))
				i = echo_variable(s, data, &ret, i);
			else if (s[i])
				ret = clean_ft_strjoin(ret, ft_substr(s, i, 1));
			if (!s[i])
				break ;
		}
		free(s);
		return (ret);
	}
	return (NULL);
}

char			*echo_str(char *str, t_data *data)
{
	char	*ret;

	if (!str[0])
		return (ft_strdup("\0"));
	ret = get_s(str, data);
	if (ret == NULL)
		ret = echo_str_sgl(str);
	return (ret);
}
