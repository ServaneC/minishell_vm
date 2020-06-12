/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:56:33 by schene            #+#    #+#             */
/*   Updated: 2020/06/12 11:34:47 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			handling_stdin(t_data *data, int start)
{
	static int	saved_input;

	if (start && (fill_fd(data) == -1 || find_input(data) == -1))
	{
		data->status = 1;
		return (-1);
	}
	if (data->input != 0 && start)
	{
		saved_input = dup(STDIN_FILENO);
		dup2(data->input, STDIN_FILENO);
	}
	else if (saved_input && !start)
	{
		dup2(saved_input, STDIN_FILENO);
		close(saved_input);
		data->input = 0;
		saved_input = 0;
	}
	return (0);
}

int			fd_handling(t_data *data, int start)
{
	static int	saved_stdout;

	if (start && handling_stdin(data, 1) == -1)
		return (-1);
	if (data->output && start && data->line[0])
	{
		saved_stdout = dup(STDOUT_FILENO);
		dup2(data->output, STDOUT_FILENO);
	}
	if (saved_stdout && !start)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		saved_stdout = 0;
		data->output = 0;
	}
	if (!start)
		handling_stdin(data, 0);
	return (0);
}
