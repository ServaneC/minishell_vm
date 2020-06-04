/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:50:13 by schene            #+#    #+#             */
/*   Updated: 2020/06/04 15:39:19 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		input_r(char *line, int i)
{
	if (i > 0)
	{
		return (line[i] == '<' && line[i - 1] != '<' && ((line[i + 1] &&
			line[i + 1] != '<')));
	}
	return (line[i] == '<' && ((line[i + 1] && line[i + 1] != '<')));
}

static int		ft_error(char **name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free(*name);
	return (-1);
}

static int		open_fd(t_data *data, char *name, int i)
{
	int		my_fd;

	my_fd = open(name, O_RDONLY);
	if (my_fd == -1)
		return (ft_error(&name));
	data->input = my_fd;
	free(name);
	return (i);
}

static int		fill_name(t_data *data, int i, int len)
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
		if (input_r(data->line, i))
		{
			i--;
			break ;
		}
		len++;
		i++;
	}
	return (open_fd(data, ft_substr(data->line, start, len), i));
}

static char		*return_free(char **str)
{
	free(*str);
	return (NULL);
}

static char		*new_line_input(t_data *data, int i, int j, char *tmp)
{
	char	c;

	while (data->line[++i])
	{
		if (data->line[i] == '\'' || data->line[i] == '\"')
		{
			c = data->line[i];
			tmp[++j] = c;
			while (data->line[++i] != c)
				tmp[++j] = data->line[i];
			tmp[++j] = data->line[i];
		}
		else if (input_r(data->line, i))
		{
			if ((i = fill_name(data, i, 0)) == -1)
				return (return_free(&tmp));
			tmp[++j] = ' ';
		}
		else
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
	data->line = ft_strtrim(tmp, " \n\t");
	free(tmp);
	return (1);
}
