/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 11:26:54 by schene            #+#    #+#             */
/*   Updated: 2020/06/03 12:12:46 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		ret = clean_ft_strjoin(ret, echo_str_sgl(str));
	return (ret);
}

static int		echo_next(t_data *data, char *cmd)
{
	int		ret;
	int		j;
	char	*str;
	char	**tab;

	tab = tab_of_quotes(cmd);
	j = -1;
	ret = 0;
	while (tab[++j])
	{
		str = echo_str(tab[j], data);
		if (str[0])
			ret++;
		free(str);
	}
	ft_free(tab);
	return (ret);
}

static void		fill_to_print(t_data *data, char **to_p, int i)
{
	int		j;
	int		chg;
	char	*str;
	char	**tab;

	*to_p = ft_strdup("\0");
	while (data->cmd[++i])
	{
		tab = tab_of_quotes(data->cmd[i]);
		j = -1;
		while (tab[++j])
		{
			chg = 1;
			str = echo_str(tab[j], data);
			if (!str[0])
				chg = 0;
			*to_p = clean_ft_strjoin(*to_p, str);
		}
		if (data->cmd[i + 1] && echo_next(data, data->cmd[i + 1]) && *to_p[0])
			*to_p = clean_ft_strjoin(*to_p, ft_strdup(" "));
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
	data->status = 0;
	if (data->cmd[1] && (ft_strncmp(data->cmd[1], "-n", 3) == 0))
		ft_putstr(to_print);
	else
		ft_putendl_fd(to_print, 1);
	free(to_print);
}
