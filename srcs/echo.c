/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:26:00 by schene            #+#    #+#             */
/*   Updated: 2020/05/23 15:31:18 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*variable_value(t_list *env, char *var)
{
	char	*name;

	name = &var[1];
	while (env->next)
	{
		if (ft_strncmp(env->content, name, ft_strlen(name)) == 0)
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

void		builtin_echo(t_list *env, char **cmd, int status, char *line)
{
	char	*str;
	char	*to_print;
	int		i;

	str = NULL;
	(void)line;
	to_print = ft_strdup("\0");
	if (cmd[1] && ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) == 0)
	{
		i = 1;
		while (cmd[++i])
		{
			if (i > 2 && str)
				to_print = ft_strjoin(to_print, " ");
			str = echo_str(cmd[i], status, env);
			if (str)
				to_print = ft_strjoin(to_print, str);
		}
		ft_putstr(to_print);
	}
	else
	{
		i = 0;
		while (cmd[++i])
		{
			if (i > 1 && str)
				to_print = ft_strjoin(to_print, " ");
			str = echo_str(cmd[i], status, env);
			if (str)
				to_print = ft_strjoin(to_print, str);
		}
		ft_putendl_fd(to_print, 1);
	}
	free(to_print);
}
