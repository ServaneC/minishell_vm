/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:50:13 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 17:42:05 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		open_fd(t_data *data, char *name, int i)
{
	int		my_fd;
	char	*tmp;

	tmp = echo_str(name, data, 0);
	free(name);
	name = tmp;
	my_fd = open(name, O_RDONLY);
	if (my_fd == -1)
		return (ft_error(&name));
	data->input = my_fd;
	free(name);
	return (i);
}

static int		input_name(t_data *data, int i, int len)
{
	int		start;
	char	c;

	i++;
	while (ft_isspace(data->line[i]))
		i++;
	start = i;
	if (data->line[i] == '\'' || data->line[i] == '\"')
	{
		c = data->line[i];
		len++;
		while (data->line[++i] != c)
			len++;
	}
	while (data->line[i] && !(ft_isspace(data->line[i])))
	{
		if (simple_r(data->line, i, '<'))
		{
			i--;
			break ;
		}
		len++;
		i++;
	}
	return (open_fd(data, ft_substr(data->line, start, len), i));
}

static char		*new_line_input(t_data *data, int i, int j, char *tmp)
{
	char	c;

	while (data->line[++i])
	{
		if (data->line[i] == '\'' || data->line[i] == '\"')
		{
			tmp[++j] = get_c_input(&c, data->line[i]);
			while (data->line[++i] && data->line[i] != c)
				tmp[++j] = data->line[i];
			if (data->line[i])
				tmp[++j] = data->line[i];
		}
		else if (simple_r(data->line, i, '<'))
		{
			if ((i = input_name(data, i, 0)) == -1)
				return (return_free(&tmp));
			tmp[++j] = ' ';
		}
		else if (data->line[i])
			tmp[++j] = data->line[i];
		if (!data->line[i])
			break ;
	}
	tmp[++j] = '\0';
	return (tmp);
}

int				find_input(t_data *data)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(data->line) + 1)))
		return (-1);
	if ((tmp = new_line_input(data, -1, -1, tmp)) == NULL)
		return (-1);
	free(data->line);
	data->line = ft_strdup(tmp);
	free(tmp);
	return (1);
}
