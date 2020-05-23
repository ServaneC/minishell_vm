/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:49:51 by schene            #+#    #+#             */
/*   Updated: 2020/05/23 15:50:50 by schene           ###   ########.fr       */
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
		buf = malloc(sizeof(struct stat));
		i = -1;
		while (path_tab[++i])
		{
			if (!(bin = malloc(sizeof(char *) * (ft_strlen(path_tab[i]) +
				ft_strlen(cmd[0]) + 2))))
				break ;
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

void	exec_line(t_list *env, char *line, int status)
{
	char	**cmd;
	char	*save;

	cmd = split_spaces(line, " \n\t");
	if (cmd[0] && is_builtin(cmd[0]))
		exec_builtin(cmd, env, status, line);
	else if (cmd[0])
	{
		save = ft_strdup(cmd[0]);
		get_path(env, cmd);
		if (cmd[0] != NULL)
			status = exec_cmd(cmd);
		else
		{
			status = 127;
			ft_printf("minishell: command not found: %s\n", save);
		}
		free(save);
		save = NULL;
	}
	ft_free(cmd);
}

int		main(int ac, char **av, char **env)
{
	int		status;
	char	*line;
	char	**multi;
	t_list	*my_env;
	int		i;

	(void)ac;
	(void)av;
	ft_putstr("minishell>> ");
	signal(SIGINT, &ctr_c);
	my_env = create_env(env);
	status = 0;
	while (get_next_line(0, &line) > 0)
	{
		i = -1;
		multi = split_quotes(line);
		while (multi[++i])
		{
			exec_line(my_env, multi[i], status);
		}
		ft_free(multi);
		ft_putstr("minishell>> ");
	}
	ft_putendl_fd("Bye !", 1);
	exit(EXIT_SUCCESS);
	return (0);
}
