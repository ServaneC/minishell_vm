/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 17:27:33 by schene            #+#    #+#             */
/*   Updated: 2020/06/12 11:36:19 by schene           ###   ########.fr       */
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
	if (data->input)
		close(data->input);
	if (data->output)
		close(data->output);
	data->input = 0;
	data->output = 0;
}

int		is_quotes(char *str, int i)
{
	return (str[i] && (str[i] == '\"' || str[i] == '\'') && is_meta(str, i));
}
