/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/06/03 18:08:28 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		check_double_rdrct(char *line, int i)
{
	if (i > 0)
	{
		return (line[i] == '>' && line[i - 1] != '>' && (line[i + 1] &&
			line[i + 1] == '>') && ((line[i + 2] && line[i + 2] != '>')));
	}
	return (line[i] == '>' && (line[i + 1] && line[i + 1] == '>') &&
		((line[i + 2] && line[i + 2] != '>')));
}

static int		check_simple_rdrct(char *line, int i)
{
	if (i > 0)
	{
		return (line[i] == '>' && line[i - 1] != '>' && ((line[i + 1] &&
			line[i + 1] != '>')));
	}
	return (line[i] == '>' && ((line[i + 1] && line[i + 1] != '>')));
}

static void		add_fd(t_data *data, char *name, int d)
{
	int		my_fd;
	int		*ptr;
	t_list	*new_fd;

	my_fd = -1;
	if (d)
		my_fd = open(name, O_WRONLY | O_APPEND);
	if (my_fd == -1)
		my_fd = open(name,
			O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	if (my_fd != -1)
	{
		ptr = malloc(sizeof(int *) * 4);
		ft_bzero(ptr, 16);
		ptr = ft_memcpy(ptr, &my_fd, 16);
		new_fd = ft_lstnew(ptr);
		ft_lstadd_back(&data->fd, new_fd);
	}
	free(name);
}

static int		fill_name(t_data *data, int i)
{
	int		start;
	char	c;
	int		d;
	int		len;

	d = 0;
	if (check_double_rdrct(data->line, i))
		d = 1;
	i += 1 + d;
	len = 0;
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
		if (check_simple_rdrct(data->line, i) || check_double_rdrct(data->line, i))
		{
			i--;
			break ;
		}
		len++;
		i++;
	}
	add_fd(data, ft_substr(data->line, start, len), d);
	return (i);
}

static int		new_line(t_data *data)
{
	char	*tmp;
	int		i;
	int		j;
	char	c;

	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(data->line) + 1)))
		return (-1);
	i = -1;
	j = -1;
	while (data->line[++i])
	{
		if (data->line[i] == '\'' || data->line[i] == '\"')
		{
			c = data->line[i];
			tmp[++j] = data->line[i];
			while (data->line[++i] != c)
				tmp[++j] = data->line[i];
			tmp[++j] = data->line[i];
		}
		else if (check_simple_rdrct(data->line, i) ||
			check_double_rdrct(data->line, i))
		{
			i = fill_name(data, i);
			tmp[++j] = ' ';
		}
		else
			tmp[++j] = data->line[i];
		if (!data->line[i])
			break ;
	}
	tmp[++j] = '\0';
	free(data->line);
	data->line = ft_strdup(tmp);
	free(tmp);
	return (1);
}

void			fill_fd(t_data *data)
{
	char	*tmp;

	new_line(data);
	tmp = ft_strtrim(data->line, " \n\t");
	free(data->line);
	data->line = tmp;
}
