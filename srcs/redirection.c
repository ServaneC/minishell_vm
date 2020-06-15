/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/06/15 16:37:07 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				double_r(char *line, int i)
{
	if (!is_meta(line, i))
		return (0);
	if (i > 0)
	{
		return ((line[i] == '>' && (line[i - 1] != '>' ||
			!is_meta(line, i - 1)) && (line[i + 1] && line[i + 1] == '>')
				&& ((line[i + 2] && line[i + 2] != '>'))));
	}
	return (line[i] == '>' && (line[i + 1] && line[i + 1] == '>') &&
		((line[i + 2] && line[i + 2] != '>')));
}

static int		add_fd(t_data *data, char *name, int d, int i)
{
	int		my_fd;
	char	*tmp;

	my_fd = -1;
	tmp = escape_str(name, data);
	free(name);
	name = tmp;
	if (data->output)
		close(data->output);
	data->output = 0;
	if (d)
		my_fd = open(name, O_WRONLY | O_APPEND);
	if (my_fd == -1 && errno != EACCES)
		my_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	if (my_fd == -1)
		return (ft_error(&name));
	data->output = my_fd;
	free(name);
	return (i);
}

static int		fill_name(t_data *data, int i, int d, int len)
{
	int		start;
	char	c;

	i += 1 + d;
	while (ft_isspace(data->line[i]))
		i++;
	start = i;
	if (is_quotes(data->line, i))
	{
		c = data->line[i];
		len++;
		while (check_char_q(data->line, ++i, c))
			len++;
	}
	while (data->line[i] && !(ft_isspace(data->line[i])))
	{
		if (simple_r(data->line, i, '>') || double_r(data->line, i))
		{
			i--;
			break ;
		}
		len++;
		i++;
	}
	return (add_fd(data, ft_substr(data->line, start, len), d, i));
}

static char		*new_line(t_data *data, int i, int j, char *tmp)
{
	char	c;

	while (data->line[++i])
	{
		if (is_quotes(data->line, i))
		{
			tmp[++j] = get_c_input(&c, data->line[i]);
			while (check_char_q(data->line, ++i, c))
				tmp[++j] = data->line[i];
			if (data->line[i])
				tmp[++j] = data->line[i];
		}
		else if (simple_r(data->line, i, '>') || double_r(data->line, i))
		{
			if ((i = fill_name(data, i, double_r(data->line, i), 0)) == -1)
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

int				fill_fd(t_data *data)
{
	char	*tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(data->line) + 1)))
		return (-1);
	if ((tmp = new_line(data, -1, -1, tmp)) == NULL)
		return (-1);
	free(data->line);
	if (tmp[0] && ft_isspace(tmp[0]) && !tmp[1])
		data->line = ft_strdup("\0");
	else
		data->line = ft_strdup(tmp);
	free(tmp);
	return (1);
}
