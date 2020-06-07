/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:46:45 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 16:14:00 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		print_parse_error(char c)
{
	ft_putstr_fd("minishell: parse error near ' ", 2);
	if (c == 'n')
		ft_putchar_fd('\\', 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\'", 2);
	return (1);
}

static int		check_exception(char *s, int i)
{
	char	c;

	c = s[i];
	if ((c == ';' && (simple_r(s, i + 1, '>') ||
		simple_r(s, i + 1, '<'))) || double_r(s, i))
		i += 2;
	else if (c == ';' && double_r(s, i + 1))
		i += 3;
	else if (simple_r(s, i, '>') || simple_r(s, i, '<'))
		i += 1;
	while (s[++i] && ft_isspace(s[i]))
		;
	return (i);
}

int				parse_error(char *s)
{
	int		i;
	char	c;

	i = -1;
	if (s[0] == '|')
		return (print_parse_error(s[0]));
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i];
			while (s[++i] && s[i] != c)
				;
		}
		else if (s[i] == ';' || s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			i = check_exception(s, i);
			if (s[i] && (s[i] == ';'
				|| s[i] == '>' || s[i] == '<' || s[i] == '|'))
				return (print_parse_error(s[i]));
		}
		if (!s[i])
			break ;
	}
	return (0);
}
