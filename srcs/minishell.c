/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:49:51 by schene            #+#    #+#             */
/*   Updated: 2020/05/27 17:40:25 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		ctr_c(int num)
{
	(void)num;
	ft_putstr("\nminishell>> ");
}

static t_data	*init_data(char **main_env)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->env = create_env(main_env);
	data->cmd = NULL;
	data->fd = 1;
	data->line = NULL;
	data->multi = NULL;
	data->status = 0;
	return (data);
}

static void		exec_shell(t_data *data, char *line)
{
	int		i;

	i = -1;
	line = rm_sgl_quote(line);
	data->multi = split_quotes(line);
	free(line);
	if (data->multi)
	{
		while (data->multi[++i])
		{
			data->line = data->multi[i];
			exec_line(data);
		}
		ft_free(data->multi);
		data->multi = NULL;
	}
	ft_putstr("minishell>> ");
}

int				main(int ac, char **av, char **env)
{
	char	*line;
	t_data	*data;

	(void)ac;
	(void)av;
	ft_putstr("minishell>> ");
	signal(SIGINT, &ctr_c);
	data = init_data(env);
	while (get_next_line(0, &line) > 0)
		exec_shell(data, line);
	if (line)
		free(line);
	ft_putendl_fd("Bye !", 1);
	builtin_exit(data);
	return (0);
}
