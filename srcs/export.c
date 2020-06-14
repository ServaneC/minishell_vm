/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 14:45:45 by schene            #+#    #+#             */
/*   Updated: 2020/06/14 16:40:41 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		print_elem_export(void *str)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putendl_fd((char *)str, 1);
}

void			print_export(t_data *data)
{
	data->status = 0;
	ft_lstiter(data->env, &print_elem_export);
}
