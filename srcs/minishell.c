/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:49:51 by schene            #+#    #+#             */
/*   Updated: 2020/06/15 16:07:20 by schene           ###   ########.fr       */
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

static t_data		*init_data(char **main_env)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->env = create_env(main_env);
	data->cmd = NULL;
	data->output = 0;
	data->line = NULL;
	data->multi = NULL;
	data->pipe = NULL;
	data->dir = ft_strdup(var_value(data->env, "$PWD"));
	data->status = 0;
	data->input = 0;
	return (data);
}

static void			exec_shell(t_data *data, char *line)
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

void				get_user_input(t_data *data, char **line)
{
	while (get_next_line(0, line) > 0)
	{
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
	ft_putstr_fd("minishell>> ", 2);
	signal(SIGINT, &ctr_c);
	signal(SIGQUIT, &ctr_q);
	data = init_data(env);
	get_user_input(data, &line);
	if (line)
		free(line);
	builtin_exit(data, 1);
	return (0);
}
