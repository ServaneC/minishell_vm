/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:48:44 by schene            #+#    #+#             */
/*   Updated: 2020/05/27 17:53:41 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		create_path(char **cmd, char *path)
{
	struct stat	*buf;
	char		**p_tab;
	char		*bin;
	char		*tmp;
	int			i;

	p_tab = ft_split(path, ':');
	buf = (struct stat *)malloc(sizeof(struct stat));
	i = -1;
	while (p_tab[++i])
	{
		bin = ft_strjoin(p_tab[i], "/");
		tmp = ft_strjoin(bin, cmd[0]);
		free(bin);
		bin = tmp;
		if (stat(bin, buf) == 0)
			break ;
		free(bin);
		bin = NULL;
	}
	ft_free(p_tab);
	free(cmd[0]);
	free(buf);
	cmd[0] = bin;
}

void			get_path(t_list *env, char **cmd)
{
	char		*path;

	path = ft_strdup(variable_value(env, "$PATH"));
	if (cmd[0][0] != '/' && (ft_strncmp(cmd[0], "./", 2) != 0))
		create_path(cmd, path);
	free(path);
	path = NULL;
}

static int		exec_cmd(char **cmd, t_list *env)
{
	pid_t	pid;
	char	**tab_env;
	int		status;

	pid = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		ft_putendl_fd(strerror(errno), 2);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		tab_env = convert_env_to_tab(env);
		if (execve(cmd[0], cmd, tab_env) == -1)
			ft_putendl_fd(strerror(errno), 2);
		free(tab_env);
		exit(EXIT_FAILURE);
	}
	if (status > 255)
		status -= 255;
	return (status);
}

void			exec_line(t_data *data)
{
	char	*save;

	data->cmd = split_spaces(data->line, " \n\t");
	if (data->cmd[0] && is_builtin(data->cmd[0]))
		exec_builtin(data);
	else if (data->cmd[0])
	{
		save = ft_strdup(data->cmd[0]);
		get_path(data->env, data->cmd);
		if (data->cmd[0] != NULL)
			data->status = exec_cmd(data->cmd, data->env);
		else
		{
			data->status = 127;
			ft_putstr("minishell: command not found: ");
			ft_putendl_fd(save, 2);
			data->cmd[0] = ft_strdup("null");
		}
		free(save);
		save = NULL;
	}
	ft_free(data->cmd);
	data->cmd = NULL;
}
