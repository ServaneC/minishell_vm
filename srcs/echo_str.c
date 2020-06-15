/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 14:37:25 by schene            #+#    #+#             */
/*   Updated: 2020/06/15 16:09:15 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				echo_variable(char *s, t_data *data, char **ret, int i)
{
	int		x;
	char	*value;

	if (s[i + 1] == '?')
	{
		*ret = clean_ft_strjoin(*ret, ft_itoa(data->status));
		return (i + 1);
	}
	else
	{
		if (var_value(data->env, &s[i]) != NULL)
		{
			value = var_value(data->env, &s[i]);
			x = -1;
			while (value[++x] && !is_quotes(value, x))
				*ret = clean_ft_strjoin(*ret, ft_substr(value, x, 1));
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

	i = 0;
	ret = ft_strdup("\0");
	while (str[++i])
	{
		if (!str[i] || str[i] == '\'')
			break ;
		ret = clean_ft_strjoin(ret, ft_substr(str, i, 1));
	}
	return (ret);
}

static char		*escape_str(char *str, t_data *data)
{
	char	*ret;
	int		i;

	i = -1;
	ret = ft_strdup("\0");
	if (str[0] == '\\' && !str[1])
		return(clean_ft_strjoin(ret, ft_strdup(" ")));
	while (str[++i])
	{
		if (str[i] == '\'' && is_meta(str, i))
		{
			ret = clean_ft_strjoin(ret, echo_str_sgl(&str[i]));
			while (str[++i] && str[i] != '\'')
				;
		}
		else if (str[i] && str[i] == '\"' && is_meta(str, i))
		{
			if (i == 0 && str[i + 1] && str[i + 1] == '\"' && !str[i + 2])
				ret = clean_ft_strjoin(ret, ft_strdup(" "));
			else if (str[i + 1])
			{
				while (str[++i])
				{
					if (str[i] == '\"' && is_meta(str, i))
						break ;
					else if (str[i] == '$' && is_meta(str, i) && str[i + 1] 
						&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
						i = echo_variable(str, data, &ret, i);
					else if (str[i])
					{
						if (str[i] == '\\' && str[i + 1] && (str[i + 1] == '\\' ||
							str[i + 1] == '$' || str[i + 1] == '\"'))
							i++;
						if (str[i])
							ret = clean_ft_strjoin(ret, ft_substr(str, i, 1));
					}
				}
			}

		}
		else if (str[i])
		{
			if (str[i] == '$' && is_meta(str, i) && str[i + 1] &&
				str[i + 1] != '\\' && (ft_isalnum(str[i + 1]) ||
				str[i + 1] == '_' || str[i + 1] == '?'))
				i = echo_variable(str, data, &ret, i);
			else if (str[i])
			{
				if (str[i] == '\\')
					i++;
				if (str[i])
					ret = clean_ft_strjoin(ret, ft_substr(str, i, 1));
			}
		}
	}
	return (ret);
}

char			*echo_str(char *str, t_data *data)
{
	char	*ret;

	if (!str[0])
		return (ft_strdup("\0"));
	ret = escape_str(str, data);
	return (ret);
}
