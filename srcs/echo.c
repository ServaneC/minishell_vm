/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:26:00 by schene            #+#    #+#             */
/*   Updated: 2020/05/25 17:55:18 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*variable_value(t_list *env, char *var)
{
	char	*name;
	int		len;

	name = &var[1];
	while (env->next)
	{
		len = (ft_strlen(env->content) - ft_strlen(ft_strchr(env->content, '=')));
		if (ft_strncmp(env->content, name, len) == 0)
			return (ft_strrchr(env->content, '=') + 1);
		env = env->next;
	}
	return (NULL);
}

char		*echo_str(char *cmd, int status, t_list *env)
{
	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '$' && cmd[1])
	{
		if (cmd[1] == '?')
			return (ft_itoa(status));
		else
			return (variable_value(env, cmd));
	}
	else
		return (cmd);
}

void		builtin_echo(t_data *data)
{
	char	*str;
	char	*to_print;
	char	*tmp;
	int		i;

	str = NULL;
	to_print = ft_strdup("\0");
	if (data->cmd[1] && ft_strncmp(data->cmd[1], "-n", ft_strlen(data->cmd[1])) == 0)
	{
		i = 1;
		while (data->cmd[++i])
		{
			if (i > 2 && str)
			{
				tmp = ft_strjoin(to_print, str);
				free(to_print);
				to_print = tmp;
			}
			str = echo_str(data->cmd[i], data->status, data->env);
			if (str)
			{
				tmp = ft_strjoin(to_print, str);
				free(to_print);
				to_print = tmp;
			}
		}
		ft_putstr(to_print);
	}
	else
	{
		i = 0;
		while (data->cmd[++i])
		{
			if (i > 1 && str)
			{
				tmp = ft_strjoin(to_print, str);
				free(to_print);
				to_print = tmp;
			}
			str = echo_str(data->cmd[i], data->status, data->env);
			if (str)
			{
				tmp = ft_strjoin(to_print, str);
				free(to_print);
				to_print = tmp;
			}
		}
		ft_putendl_fd(to_print, 1);
	}
	free(to_print);
}
