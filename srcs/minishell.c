/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:49:51 by schene            #+#    #+#             */
/*   Updated: 2020/06/04 16:16:52 by schene           ###   ########.fr       */
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
		ft_putstr("minishell>> ");
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
	data->fd = NULL;
	data->line = NULL;
	data->multi = NULL;
	data->status = 0;
	data->input = 0;
	return (data);
}

static void			exec_shell(t_data *data, char *line)
{
	int		i;

	i = -1;
	if (check_parse_error(line) == 0)
	{
		line = rm_sgl_quote(line);
		data->multi = split_quotes(line);
		free(line);
		line = NULL;
		if (data->multi)
		{
			while (data->multi[++i])
			{
				data->line = ft_strtrim(data->multi[i], " \n\t");
				exec_line(data);
				close_fd(data);
			}
			ft_free(data->multi);
			data->multi = NULL;
		}
	}
	free(line);
	line = NULL;
}

int					main(int ac, char **av, char **env)
{
	char	*line;
	t_data	*data;

	(void)ac;
	(void)av;
	g_ctrl_c = 0;
	ft_putstr("minishell>> ");
	signal(SIGINT, &ctr_c);
	signal(SIGQUIT, &ctr_q);
	data = init_data(env);
	while (get_next_line(0, &line) > 0)
	{
		if (g_ctrl_c)
			data->status = 130;
		if (g_ctrl_q)
			data->status = 131;
		g_ctrl_c = 0;
		g_ctrl_q = 0;
		exec_shell(data, line);
		ft_putstr("minishell>> ");
	}
	if (line)
		free(line);
	builtin_exit(data);
	return (0);
}
