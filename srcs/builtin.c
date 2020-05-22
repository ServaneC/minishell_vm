/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:21:34 by schene            #+#    #+#             */
/*   Updated: 2020/05/22 15:01:42 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	return (0);
}

void	exec_builtin(char **cmd, t_list *env, int status, char *line)
{
	if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		builtin_cd(cmd[1], env);
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		builtin_pwd();
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		print_env(env);
	if (ft_strncmp(cmd[0], "export", 6) == 0)
		builtin_export(cmd, env);
	if (ft_strncmp(cmd[0], "unset", 5) == 0)
		builtin_unset(cmd, env);
	if (ft_strncmp(cmd[0], "exit", 4) == 0)
		builtin_exit();
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		builtin_echo(env, cmd, status, line);
}

int		change_value(t_list *env, char *name, char *newvalue)
{
	char	*new;

	new = ft_strjoin(name, "=");
	new = ft_strjoin(new, newvalue);

	while (env->next)
	{
		if (ft_strncmp(env->content, name, ft_strlen(name)) == 0)
		{
			env->content = new;
			return (1);
		}
		env = env->next;
	}
	return (0);	
}

void	builtin_cd(char *path, t_list *env)
{
	(void)env;
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

void	builtin_exit(void)
{
	exit(EXIT_SUCCESS);
}