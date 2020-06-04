/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:52:23 by schene            #+#    #+#             */
/*   Updated: 2020/06/04 16:16:24 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				check_parse_error(char *line)
{
	int	i;

	i = 1;
	line = ft_strchr(line, '>');
	if (line)
	{
		if (line[1] == '>')
			i++;
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			ft_putendl_fd("minishell: parse error near '\\n'", 2);
		else if (line[i] == '>')
			ft_putendl_fd("minishell: parse error near '>'", 2);
		else if (line[i] == ';')
			ft_putendl_fd("minishell: parse error near '>'", 2);
		if (!line[i] || line[i] == '>' || line[i] == ';')
			return (1);
		else
			return (check_parse_error(&line[i]));
	}
	return (0);
}

char			*return_free(char **str)
{
	free(*str);
	return (NULL);
}

int				simple_r(char *line, int i, char r)
{
	if (i > 0)
	{
		return (line[i] == r && line[i - 1] != r && ((line[i + 1] &&
			line[i + 1] != r)));
	}
	return (line[i] == r && ((line[i + 1] && line[i + 1] != r)));
}

int				ft_error(char **name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free(*name);
	return (-1);
}
