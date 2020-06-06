/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:52:23 by schene            #+#    #+#             */
/*   Updated: 2020/06/06 16:04:08 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int				print_parse_error(char c)
{
	ft_putstr_fd("minishell: parse error near ' ", 2);
	if (c == 'n')
		ft_putchar_fd('\\', 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\'", 2);
	return (1);
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
