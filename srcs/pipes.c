/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 12:18:34 by schene            #+#    #+#             */
/*   Updated: 2020/06/12 18:08:00 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		exec_pipe(t_data *data, int i, int fd, pid_t pid)
{
	int		pipefd[2];

	while (data->pipe[i])
	{
		if (pipe(pipefd) == -1 || (pid = fork()) == -1)
			return (ft_putendl_fd(strerror(errno), 2));
		else if (pid == 0)
		{
			data->line = ft_strdup(data->pipe[i]);
			dup2(fd, STDIN_FILENO);
			if (data->pipe[i + 1])
				dup2(pipefd[WR_END], STDOUT_FILENO);
			close(pipefd[RD_END]);
			exec_line(data);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &data->status, 0);
			kill(pid, SIGTERM);
			close(pipefd[WR_END]);
			fd = pipefd[RD_END];
			i++;
		}
	}
}

void			handle_pipe(t_data *data)
{
	if (!data->pipe[1])
	{
		data->line = ft_strdup(data->pipe[0]);
		return (exec_line(data));
	}
	exec_pipe(data, 0, 0, -1);
	if (data->status >= 255)
		data->status -= 255;
}
