/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/06/02 18:53:13 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		check_simple_rdrct(char *line, int k)
{
	if (k > 0)
	{
		return (line[k] == '>' && line[k - 1] != '>' && ((line[k + 1] &&
			line[k + 1] != '>') || !(line[k + 1])));
	}
	return (line[k] == '>' && ((line[k + 1] && line[k + 1] != '>') ||
		!(line[k + 1])));
}

static int		fill_name(t_data *data, t_list **name, int i)
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
		while (data->line[++i] != c)
			;
	}
	while (data->line[i] && !(ft_isspace(data->line[i])))
	{
		if (check_simple_rdrct(data->line, i))
		{
			i--;
			break ;
		}
		i++;
	}
	ft_lstadd_back(name, ft_lstnew(ft_substr(data->line, start, i - start)));
	return (i);
}

static t_list	*new_line(t_data *data)
{
	t_list	*name;
	char	*tmp;
	int		i;
	int		j;
	char	c;

	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(data->line) + 1)))
		return (NULL);
	i = -1;
	j = -1;
	name = NULL;
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
		else if (check_simple_rdrct(data->line, i))
		{
			i = fill_name(data, &name, i);
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
	return (name);
}

void			fill_fd(t_data *data)
{
	t_list	*tmp;
	t_list	*name;
	t_list	*new_fd;
	int		my_fd;
	int		*ptr;

	name = new_line(data);
	while (name)
	{
		tmp = name;
		name = name->next;
		tmp->content = remove_quotes(tmp->content);
		my_fd = open(tmp->content,
			O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
		if (my_fd != -1)
		{
			ptr = malloc(sizeof(int *) * 4);
			ft_bzero(ptr, 16);
			ptr = ft_memcpy(ptr, &my_fd, 16);
			new_fd = ft_lstnew(ptr);
			ft_lstadd_back(&data->fd, new_fd);
		}
		free(tmp->content);
		free(tmp);
	}
}
