/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:52:23 by schene            #+#    #+#             */
/*   Updated: 2020/06/09 16:36:52 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*return_free(char **str)
{
	free(*str);
	return (NULL);
}

int		simple_r(char *line, int i, char r)
{
	if (!is_meta(line, i))
		return (0);
	if (i > 0)
	{
		return (line[i] == r && (line[i - 1] != r || !is_meta(line, i - 1))
			&& ((line[i + 1] && line[i + 1] != r)));
	}
	return (line[i] == r && ((line[i + 1] && line[i + 1] != r)));
}

int		ft_error(char **name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(*name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free(*name);
	return (-1);
}

char	get_c_input(char *c, char str_i)
{
	*c = str_i;
	return (*c);
}

int		check_char_q(char *s, int i, char c)
{
	if (!s[i])
		return (0);
	if (s[i] == c && is_meta(s, i))
		return (0);
	return (1);
}
