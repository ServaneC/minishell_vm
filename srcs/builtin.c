/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:21:34 by schene            #+#    #+#             */
/*   Updated: 2020/05/27 15:40:34 by schene           ###   ########.fr       */
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

void	exec_builtin(t_data *data)
{
	int	len;

	len = ft_strlen(data->cmd[0]);
	if (ft_strncmp(data->cmd[0], "cd", len) == 0)
		builtin_cd(data->cmd[1], data->env);
	if (ft_strncmp(data->cmd[0], "pwd", len) == 0)
		builtin_pwd();
	if (ft_strncmp(data->cmd[0], "env", len) == 0)
		print_env(data->env);
	if (ft_strncmp(data->cmd[0], "export", len) == 0)
		builtin_export(data);
	if (ft_strncmp(data->cmd[0], "unset", len) == 0)
		builtin_unset(data->cmd, data->env);
	if (ft_strncmp(data->cmd[0], "exit", len) == 0)
		builtin_exit(data);
	if (ft_strncmp(data->cmd[0], "echo", len) == 0)
		builtin_echo(data);
}

void	builtin_pwd(void)
{
	char	cwd[MAX_PATH];

	if (getcwd(cwd, MAX_PATH) != NULL)
		ft_putendl_fd(cwd, 1);
	else
		ft_putendl_fd(strerror(errno), 2);
}

void	builtin_exit(t_data *data)
{
	t_list *tmp;

	if (data->cmd)
		ft_free(data->cmd);
	if (data->multi)
		ft_free(data->multi);
	while (data->env)
	{
		tmp = data->env;
		data->env = data->env->next;
		free(tmp->content);
		free(tmp);
	}
	free(data);
	exit(EXIT_SUCCESS);
}
