/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:48:44 by schene            #+#    #+#             */
/*   Updated: 2020/06/18 15:02:48 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		create_path(char **cmd, char *path, int i)
{
	char		**p_tab;
	char		*bin;
	char		*tmp;

	p_tab = ft_split(path, ':');
	while (p_tab[++i])
	{
		bin = ft_strjoin(p_tab[i], "/");
		tmp = ft_strjoin(bin, cmd[0]);
		free(bin);
		bin = tmp;
		if (try_path(bin) == 0)
			break ;
		free(bin);
		bin = NULL;
	}
	ft_free(p_tab);
	free(cmd[0]);
	cmd[0] = bin;
}

static void		exec_cmd(t_data *data, char **save)
{
	char	**tab_env;

	free(*save);
	g_child_pid = 0;
	g_child_pid = fork();
	if (g_child_pid == -1)
		ft_putendl_fd(strerror(errno), 2);
	else if (g_child_pid > 0)
	{
		waitpid(g_child_pid, &data->status, 0);
		kill(g_child_pid, SIGTERM);
	}
	else
	{
		tab_env = convert_env_to_tab(data->env);
		if (execve(data->cmd[0], data->cmd, tab_env) == -1)
			ft_putendl_fd(strerror(errno), 2);
		free(tab_env);
		exit(data->status);
	}
	if (data->status > 255)
		data->status -= 255;
	g_child_pid = 0;
}

static void		exec_path(t_data *data, char *path)
{
	char	*save;

	save = ft_strdup(data->cmd[0]);
	if (path == NULL)
	{
		free(data->cmd[0]);
		data->cmd[0] = NULL;
		errno = 2;
	}
	else if (data->cmd[0][0] != '/' && (ft_strncmp(data->cmd[0], "./", 2) != 0))
		create_path(data->cmd, path, -1);
	free(path);
	path = NULL;
	if (data->cmd[0] && try_path(data->cmd[0]) == 0)
		exec_cmd(data, &save);
	else
	{
		data->status = 127;
		if (errno != 2)
			data->status = 126;
		if (!data->cmd[0])
			data->cmd[0] = ft_strdup(save);
		free(save);
		print_exec_error(data->cmd[0]);
	}
}

void			exec_line(t_data *data)
{
	int		saved_stdout;
	int		i;
	char	*tmp;

	i = -1;
	saved_stdout = fd_handling(data, 1);
	if (data->line[0] && saved_stdout != -1)
	{
		data->cmd = split_spaces(data->line, " \n\t\v\r\f");
		while (data->cmd[++i])
		{
			tmp = escape_str(data->cmd[i], data);
			free(data->cmd[i]);
			data->cmd[i] = tmp;
		}
		if (data->cmd[0] && is_builtin(data->cmd[0]))
			exec_builtin(data);
		else if (data->cmd[0])
			exec_path(data, ft_strdup(var_value(data->env, "$PATH")));
		ft_free(data->cmd);
		data->cmd = NULL;
	}
	fd_handling(data, 0);
	free(data->line);
	data->line = NULL;
}

void			exec_shell(t_data *data, char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = contains_comment(line);
	free(line);
	line = tmp;
	data->multi = split_spaces(line, ";");
	free(line);
	line = NULL;
	tmp = NULL;
	if (data->multi)
	{
		while (data->multi[++i])
		{
			data->pipe = split_spaces(data->multi[i], "|");
			handle_pipe(data, i);
			close_fd(data);
			ft_free(data->pipe);
			data->pipe = NULL;
		}
		ft_free(data->multi);
		data->multi = NULL;
	}
}
