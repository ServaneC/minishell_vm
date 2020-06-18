/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:49:51 by schene            #+#    #+#             */
/*   Updated: 2020/06/18 15:00:21 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	g_ctrl_c;
static int	g_ctrl_q;

static void			ctr_c(int num)
{
	(void)num;
	g_ctrl_c = 1;
	ft_putchar_fd('\n', 1);
	if (g_child_pid == 0)
		ft_putstr_fd("minishell>> ", 2);
}

static void			ctr_q(int num)
{
	(void)num;
	if (g_child_pid > 0)
	{
		g_ctrl_q = 1;
		kill(g_child_pid, SIGQUIT);
		ft_putstr_fd("quit (core dumped)\n", 1);
	}
}

void				rm_save(char **line, char **save)
{
	char	*tmp;

	if (g_ctrl_c && *save)
	{
		tmp = ft_substr(*line, ft_strlen(*save), ft_strlen(*line));
		free(*line);
		*line = tmp;
	}
	if (*save)
	{
		free(*save);
		*save = NULL;
	}
}

void				get_user_input(t_data *data, char **line)
{
	char	*save;

	save = NULL;
	if (*line != NULL)
		save = ft_strdup(*line);
	if (g_ctrl_c)
		printf("control_c\n");
	while (get_next_line(0, line) > 0)
	{
		rm_save(line, &save);
		if (g_ctrl_c || g_ctrl_q)
			data->status = 130 + g_ctrl_q;
		g_ctrl_c = 0;
		g_ctrl_q = 0;
		if (parse_error(*line))
			data->status = 2;
		else
			exec_shell(data, *line);
		ft_putstr_fd("minishell>> ", 2);
	}
	if (*line && **line != '\0')
		get_user_input(data, line);
}

int					main(int ac, char **av, char **env)
{
	char	*line;
	t_data	*data;

	(void)ac;
	(void)av;
	signal(SIGINT, &ctr_c);
	signal(SIGQUIT, &ctr_q);
	ft_putstr_fd("minishell>> ", 2);
	data = init_data(env);
	line = NULL;
	get_user_input(data, &line);
	if (line)
		free(line);
	builtin_exit(data, 1);
	return (0);
}
