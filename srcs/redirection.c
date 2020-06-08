/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/06/08 13:28:58 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				double_r(char *line, int i)
{
	if (!is_meta(line, i))
		return (0);
	if (i > 0)
	{
		return ((line[i] == '>' && line[i - 1] != '>') && (line[i + 1] &&
			line[i + 1] == '>') && ((line[i + 2] && line[i + 2] != '>')));
	}
	return (line[i] == '>' && (line[i + 1] && line[i + 1] == '>') &&
		((line[i + 2] && line[i + 2] != '>')));
}

static int		add_fd(t_data *data, char *name, int d, int i)
{
	int		my_fd;
	char	*tmp;
	int		*ptr;
	t_list	*new_fd;

	my_fd = -1;
	tmp = echo_str(name, data);
	free(name);
	name = tmp;
	if (d)
		my_fd = open(name, O_WRONLY | O_APPEND);
	if (my_fd == -1 && errno != EACCES)
		my_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	if (my_fd == -1)
		return (ft_error(&name));
	ptr = malloc(sizeof(int *) * 4);
	ft_bzero(ptr, 16);
	ptr = ft_memcpy(ptr, &my_fd, 16);
	new_fd = ft_lstnew(ptr);
	ft_lstadd_back(&data->fd, new_fd);
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
	if (data->line[i] == '\'' || data->line[i] == '\"')
	{
		c = data->line[i];
		len++;
		while (data->line[++i] != c)
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
		if (data->line[i] == '\'' || data->line[i] == '\"')
		{
			tmp[++j] = get_c_input(&c, data->line[i]);
			while (data->line[++i] && data->line[i] != c)
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
