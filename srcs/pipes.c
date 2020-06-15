/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 12:18:34 by schene            #+#    #+#             */
/*   Updated: 2020/06/15 16:07:48 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		exec_child_pipe(t_data *data, int pipefd[2], int *fd, int i)
{
	close(pipefd[RD_END]);
	data->line = ft_strdup(data->pipe[i]);
	dup2(*fd, STDIN_FILENO);
	if (data->pipe[i + 1])
		dup2(pipefd[WR_END], STDOUT_FILENO);
	close(pipefd[WR_END]);
	exec_line(data);
	if (data->status > 255)
		data->status -= 255;
	return (data->status);
}

static void		exec_pipe(t_data *data, int i, int fd, pid_t pid)
{
	int		pipefd[2];

	data->status = 0;
	while (data->pipe[i])
	{
		if (pipe(pipefd) == -1 || (pid = fork()) == -1)
			return (ft_putendl_fd(strerror(errno), 2));
		else if (pid == 0)
			exit(exec_child_pipe(data, pipefd, &fd, i));
		else
		{
			close(pipefd[WR_END]);
			waitpid(pid, &data->status, 0);
			kill(pid, SIGTERM);
			if (data->pipe[i + 1])
				fd = pipefd[RD_END];
			data->status = data->status == 32512 ? 127 : data->status;
			i++;
		}
	}
}

void			handle_pipe(t_data *data, int i)
{
	if (!data->pipe[1])
	{
		data->line = ft_strdup(data->multi[i]);
		return (exec_line(data));
	}
	exec_pipe(data, 0, 0, -1);
	while (data->status > 255)
		data->status -= 255;
}
