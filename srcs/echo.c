/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 11:26:54 by schene            #+#    #+#             */
/*   Updated: 2020/05/30 16:19:10 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		echo_variable(char *s, t_data *data, char **ret, int i)
{
	char	*str;
	char	*tmp;

	if (s[i + 1] == '?')
	{
		str = ft_itoa(data->status);
		tmp = ft_strjoin(*ret, str);
		free(str);
		free(*ret);
		*ret = tmp;
		i += 1;
	}
	else
	{
		if (variable_value(data->env, &s[i]) != NULL)
		{
			tmp = ft_strjoin(*ret, variable_value(data->env, &s[i]));
			free(*ret);
			*ret = tmp;
		}
		while (s[++i] && ft_isalnum(s[i]))
			;
		i--;
	}
	return (i);
}

static char		*echo_str_sgl(char *str, t_data *data)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	*s;

	i = -1;
	(void)data;
	ret = ft_strdup("\0");
	s = ft_strtrim(str, "\'");
	while (s[++i])
	{
		str = ft_substr(s, i, 1);
		tmp = ft_strjoin(ret, str);
		free(str);
		free(ret);
		ret = tmp;
		if (!s[i])
			break ;
	}
	free(s);
	return (ret);
}

static char		*echo_str(char *str, t_data *data)
{
	int		i;
	char	*ret;
	char	*s;

	i = -1;
	ret = ft_strdup("\0");
	if (str[0] != '\'')
	{
		s = ft_strtrim(str, "\"");
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
		ret = clean_ft_strjoin(ret, echo_str_sgl(str, data));
	return (ret);
}

static void		fill_to_print(t_data *data, char **to_print, int i)
{
	int		j;
	int		change;
	char	*str;
	char	**tab;

	*to_print = ft_strdup("\0");
	while (data->cmd[++i])
	{
		tab = tab_of_quotes(data->cmd[i]);
		j = -1;
		while (tab[++j])
		{
			change = 1;
			str = echo_str(tab[j], data);
			if (!str[0])
				change = 0;
			*to_print = clean_ft_strjoin(*to_print, str);
		}
		if (data->cmd[i + 1] && change)
			*to_print = clean_ft_strjoin(*to_print, ft_strdup(" "));
		ft_free(tab);
	}
}

void			builtin_echo(t_data *data)
{
	int		i;
	char	*to_print;

	i = 0;
	if (data->cmd[1] && (ft_strncmp(data->cmd[1], "-n", 3) == 0))
		i = 1;
	fill_to_print(data, &to_print, i);
	if (data->cmd[1] && (ft_strncmp(data->cmd[1], "-n", 3) == 0))
		ft_putstr(to_print);
	else
		ft_putendl_fd(to_print, 1);
	free(to_print);
}
