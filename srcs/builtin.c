/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:21:34 by schene            #+#    #+#             */
/*   Updated: 2020/06/06 14:16:47 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		is_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	len = len < 3 ? 3 : len;
	if (ft_strncmp(cmd, "cd", len) == 0)
		return (1);
	len = len < 4 ? 4 : len;
	if (ft_strncmp(cmd, "pwd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", len) == 0)
		return (1);
	len = len < 5 ? 5 : len;
	if (ft_strncmp(cmd, "exit", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", len) == 0)
		return (1);
	len = len < 6 ? 6 : len;
	if (ft_strncmp(cmd, "unset", len) == 0)
		return (1);
	len = len < 7 ? 7 : len;
	if (ft_strncmp(cmd, "export", len) == 0)
		return (1);
	return (0);
}

void	builtin_pwd(t_data *data)
{
	char	cwd[MAX_PATH];
	char	*str;

	if (getcwd(cwd, MAX_PATH) != NULL)
		ft_putendl_fd(cwd, 1);
	else
	{
		str = var_value(data->env, "$PWD");
		ft_putendl_fd(str, 1);
	}
	data->status = 0;
}

void	exec_builtin(t_data *data)
{
	int	len;

	len = ft_strlen(data->cmd[0]);
	if (ft_strncmp(data->cmd[0], "cd", len) == 0)
		builtin_cd(data);
	if (ft_strncmp(data->cmd[0], "pwd", len) == 0)
		builtin_pwd(data);
	if (ft_strncmp(data->cmd[0], "env", len) == 0)
		print_env(data);
	if (ft_strncmp(data->cmd[0], "export", len) == 0)
		builtin_export(data);
	if (ft_strncmp(data->cmd[0], "unset", len) == 0)
		builtin_unset(data);
	if (ft_strncmp(data->cmd[0], "exit", len) == 0)
		builtin_exit(data, 0);
	if (ft_strncmp(data->cmd[0], "echo", len) == 0)
		builtin_echo(data);
}

int		get_status(t_data *data)
{
	int		i;

	if (ft_strncmp(data->cmd[0], "exit", 5) != 0)
		return (data->status);
	if (!data->cmd[1])
		return (data->status);
	if (data->cmd[1])
	{
		i = -1;
		while (data->cmd[1][++i])
		{
			if (!ft_isdigit(data->cmd[1][i]) && data->cmd[1][i] != '-')
			{
				ft_putendl_fd("minishell: exit: numeric argument necessary", 2);
				return (2);
			}
		}
		if (!data->cmd[2])
			return ((unsigned char)ft_atoi(data->cmd[1]));
	}
	data->status = 1;
	ft_putendl_fd("minishell: exit: too much arguments", 2);
	return (-1);
}

void	builtin_exit(t_data *data, int end)
{
	int status;

	ft_putstr_fd("exit\n", 2);
	status = data->status;
	if (end == 0)
		status = get_status(data);
	if (end || status != -1)
	{
		if (data->cmd)
			ft_free(data->cmd);
		if (data->multi)
			ft_free(data->multi);
		if (data->line)
			free(data->line);
		free_lst(data->env);
		close_fd(data);
		free(data->dir);
		free(data);
		exit(status);
	}
}
