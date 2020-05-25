/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:49:51 by schene            #+#    #+#             */
/*   Updated: 2020/05/25 17:31:46 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}

void	get_path(t_list *env, char **cmd)
{
	struct stat	*buf;
	char		*path;
	char		**path_tab;
	char		*bin;
	int			i;

	path = ft_strdup(variable_value(env, "$PATH"));
	bin = NULL;
	if (cmd[0][0] != '/' && (ft_strncmp(cmd[0], "./", 2) != 0))
	{
		path_tab = ft_split(path, ':');
		buf = (struct stat *)malloc(sizeof(struct stat));
		i = -1;
		while (path_tab[++i])
		{
			if (!(bin = (char *)malloc(sizeof(char *) * (ft_strlen(path_tab[i]) +
				ft_strlen(cmd[0]) + 2))))
				break ;
			bin[0] = '\0';
			ft_strlcat(bin, path_tab[i], ft_strlen(path_tab[i]) + 1);
			ft_strlcat(bin, "/", ft_strlen(path_tab[i]) + 2);
			ft_strlcat(bin, cmd[0], ft_strlen(path_tab[i]) + ft_strlen(cmd[0]) + 2);
			if (stat(bin, buf) == 0)
				break ;
			free(bin);
			bin = NULL;
		}
		ft_free(path_tab);
		free(path);
		free(cmd[0]);
		free(buf);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
}

int		exec_cmd(char **cmd)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		ft_putstr_fd(strerror(errno), 2);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			ft_putstr_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
	if (status > 255)
		status -= 255;
	return (status);
}

void	ctr_c(int num)
{
	(void)num;
	ft_putstr("\nminishell>> ");
}

char	*remove_quotes(char *cmd)
{
	char *tmp;

	if (cmd[0] == '\'')
		tmp = ft_strtrim(cmd, "\'");
	else if (cmd[0] == '\"')
		tmp = ft_strtrim(cmd, "\"");
	else
		tmp = ft_strdup(cmd);
	free(cmd);
	return (tmp);
}

t_data		*init_data(char **main_env)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->env = create_env(main_env);
	data->cmd = NULL;
	data->fd = 1;
	data->line = NULL;
	data->status = 0;
	return (data);
}

void	exec_line(t_data *data, char **multi)
{
	char	*save;

	data->cmd = split_spaces(data->line, " \n\t");
	if (data->cmd[0] && is_builtin(data->cmd[0]))
		exec_builtin(data, multi);
	else if (data->cmd[0])
	{
		save = ft_strdup(data->cmd[0]);
		get_path(data->env, data->cmd);
		if (data->cmd[0] != NULL)
			data->status = exec_cmd(data->cmd);
		else
		{
			data->status = 127;
			ft_printf("minishell: command not found: %s\n", save);
		}
		free(save);
		save = NULL;
	}
	ft_free(data->cmd);
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	char	**multi;
	t_data	*data;
	int		i;

	(void)ac;
	(void)av;
	line = NULL;
	multi = NULL;
	ft_putstr("minishell>> ");
	signal(SIGINT, &ctr_c);
	data = init_data(env);
	while (get_next_line(0, &line) > 0)
	{
		i = -1;
		multi = split_quotes(line);
		free(line);
		while (multi[++i])
		{
			data->line = multi[i];
			exec_line(data, multi);
		}
		ft_free(multi);
		multi = NULL;
		ft_putstr("minishell>> ");
	}
	if (line)
		free(line);
	ft_putendl_fd("Bye !", 1);
	builtin_exit(data, multi);
	return (0);
}
