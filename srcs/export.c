/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 14:45:45 by schene            #+#    #+#             */
/*   Updated: 2020/06/15 13:15:44 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		print_elem_export(void *str)
{
	int		i;
	char	*s;

	i = -1;
	s = ft_strdup(str);
	ft_putstr_fd("declare -x ", 1);
	while (s[++i] && s[i] != '=')
		ft_putchar_fd(s[i], 1);
	if (s[i])
	{
		ft_putstr_fd("=\"", 1);
		while (s[++i])
			ft_putchar_fd(s[i], 1);
		ft_putchar_fd('\"', 1);
	}
	ft_putchar_fd('\n', 1);
	free(s);
}

void			print_export(t_data *data)
{
	data->status = 0;
	ft_lstiter(data->env, &print_elem_export);
}
