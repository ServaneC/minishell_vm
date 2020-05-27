/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:26:00 by schene            #+#    #+#             */
/*   Updated: 2020/05/27 16:35:24 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char			*variable_value(t_list *env, char *var)
{
	char	*name;
	int		len;
	int		len2;

	name = &var[1];
	while (env)
	{
		len = (ft_strlen(env->content) -
			ft_strlen(ft_strchr(env->content, '=')));
		len2 = (ft_strlen(name) - ft_strlen(ft_strchr(name, ' ')));
		len = len2 > len ? len2 : len;
		if (ft_strncmp(env->content, name, len) == 0)
			return (ft_strrchr(env->content, '=') + 1);
		env = env->next;
	}
	return (NULL);
}

static int		echo_variable(t_data *data, int i, char **ret, int j)
{
	char	*str;
	char	*tmp;

	if (data->cmd[i][j + 1] == '?')
	{
		str = ft_itoa(data->status);
		tmp = ft_strjoin(*ret, str);
		free(str);
		free(*ret);
		*ret = tmp;
		j += 2;
	}
	else
	{
		tmp = ft_strjoin(*ret, variable_value(data->env, &data->cmd[i][j]));
		free(*ret);
		*ret = tmp;
		j++;
		while (data->cmd[i][j] && ft_isalnum(data->cmd[i][j]))
			j++;
		j--;
	}
	return (j);
}

static char		*echo_str(t_data *data, int i)
{
	char	*tmp;
	char	*str;
	char	*ret;
	int		j;

	j = -1;
	if (data->cmd[i] == NULL)
		return (NULL);
	ret = ft_strdup("\0");
	while (data->cmd[i][++j])
	{
		if (data->cmd[i][j] == '$' && data->cmd[i][j + 1] &&
			(ft_isalnum(data->cmd[i][j + 1]) || data->cmd[i][j + 1] == '?'))
			j = echo_variable(data, i, &ret, j);
		else
		{
			str = ft_substr(data->cmd[i], j, 1);
			tmp = ft_strjoin(ret, str);
			free(str);
			free(ret);
			ret = tmp;
		}
	}
	return (ret);
}

static void		fill_to_print(t_data *data, char **to_print, int i)
{
	char	*tmp;
	char	*str;

	str = echo_str(data, i);
	tmp = ft_strjoin(*to_print, str);
	free(str);
	free(*to_print);
	*to_print = tmp;
	if (data->cmd[i + 1])
	{
		str = ft_strdup(" ");
		tmp = ft_strjoin(*to_print, str);
		free(str);
		free(*to_print);
		*to_print = tmp;
	}
}

void			builtin_echo(t_data *data)
{
	int		i;
	char	*to_print;

	i = 0;
	to_print = ft_strdup("\0");
	if (data->cmd[1] && (ft_strncmp(data->cmd[1], "-n", 3) == 0))
		i = 1;
	while (data->cmd[++i])
		fill_to_print(data, &to_print, i);
	if (data->cmd[1] && (ft_strncmp(data->cmd[1], "-n", 3) == 0))
		ft_putstr(to_print);
	else
		ft_putendl_fd(to_print, 1);
	free(to_print);
}
