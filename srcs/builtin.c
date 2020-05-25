/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:21:34 by schene            #+#    #+#             */
/*   Updated: 2020/05/25 18:15:36 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_data *data)
{
	if (ft_strncmp(data->cmd[0], "cd", ft_strlen(data->cmd[0])) == 0)
		builtin_cd(data->cmd[1], data->env);
	if (ft_strncmp(data->cmd[0], "pwd", ft_strlen(data->cmd[0])) == 0)
		builtin_pwd();
	if (ft_strncmp(data->cmd[0], "env", ft_strlen(data->cmd[0])) == 0)
		print_env(data->env);
	if (ft_strncmp(data->cmd[0], "export", ft_strlen(data->cmd[0])) == 0)
		builtin_export(data->cmd, data->env);
	if (ft_strncmp(data->cmd[0], "unset", ft_strlen(data->cmd[0])) == 0)
		builtin_unset(data->cmd, data->env);
	if (ft_strncmp(data->cmd[0], "exit", ft_strlen(data->cmd[0])) == 0)
		builtin_exit(data);
	if (ft_strncmp(data->cmd[0], "echo", ft_strlen(data->cmd[0])) == 0)
		builtin_echo(data);
}

int		change_value(t_list *env, char *name, char *newvalue)
{
	char	*tmp;
	char	*new;

	tmp = ft_strjoin(name, "=");
	new = ft_strjoin(tmp, newvalue);
	free(tmp);
	while (env->next)
	{
		if (ft_strncmp(env->content, name, ft_strlen(name)) == 0)
		{
			free(env->content);
			env->content = new;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	builtin_cd(char *path, t_list *env)
{
	char	old_pwd[MAX_PATH];
	char	pwd[MAX_PATH];

	getcwd(old_pwd, MAX_PATH);
	if (path == NULL || path[0] == '$')
	{
		if (path == NULL || variable_value(env, path) == NULL)
			path = "$HOME";
		path = variable_value(env, path);
	}
	if (path[0] == '~')
		path = ft_strjoin(variable_value(env, "$HOME"), &path[1]);
	if (chdir(path) == 0)
	{
		getcwd(pwd, MAX_PATH);
		change_value(env, "PWD", pwd);
		change_value(env, "OLDPWD", old_pwd);
	}
	else
		ft_putendl_fd(strerror(errno), 2);
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
	while (data->env != NULL)
	{
		tmp = data->env;
		data->env = data->env->next;
		free(tmp->content);
		free(tmp);
	}
	free(data);
	exit(EXIT_SUCCESS);
}
