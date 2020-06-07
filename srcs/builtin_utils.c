/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 17:27:33 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 15:44:45 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lst(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	close_fd(t_data *data)
{
	t_list *tmp;

	while (data->fd)
	{
		tmp = data->fd;
		data->fd = data->fd->next;
		close(*(int *)tmp->content);
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
	data->fd = NULL;
}
