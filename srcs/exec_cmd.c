/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:48:44 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 17:30:26 by schene           ###   ########.fr       */
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
		if (lstat(bin, buf) == 0)
			break ;
		free(bin);
		bin = NULL;
	}
	ft_free(p_tab);
	free(cmd[0]);
	free(buf);
	cmd[0] = bin;
}

static void		exec_cmd(t_data *data, char **save)
{
	char	**tab_env;

	free(*save);
	g_child_pid = 0;
	data->status = 0;
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
		exit(EXIT_FAILURE);
	}
	if (data->status > 255)
		data->status -= 255;
	g_child_pid = 0;
}

static void		get_path(t_data *data, int saved_stdout)
{
	char	*path;
	char	*save;

	save = ft_strdup(data->cmd[0]);
	path = ft_strdup(var_value(data->env, "$PATH"));
	if (data->cmd[0][0] != '/' && (ft_strncmp(data->cmd[0], "./", 2) != 0))
		create_path(data->cmd, path);
	free(path);
	path = NULL;
	if (data->cmd[0] != NULL)
		exec_cmd(data, &save);
	else
	{
		data->status = 127;
		data->cmd[0] = save;
		ft_putstr_fd("minishell: command not found: ", saved_stdout);
		ft_putendl_fd(data->cmd[0], saved_stdout);
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
		data->cmd = split_spaces(data->line, " \n\t");
		while (data->cmd[++i])
		{
			tmp = echo_str(data->cmd[i], data, 1);
			free(data->cmd[i]);
			data->cmd[i] = ft_strdup(tmp);
			free(tmp);
		}
		if (data->cmd[0] && is_builtin(data->cmd[0]))
			exec_builtin(data);
		else if (data->cmd[0])
			get_path(data, saved_stdout);
		ft_free(data->cmd);
	}
	fd_handling(data, 0);
	free(data->line);
	data->line = NULL;
}
