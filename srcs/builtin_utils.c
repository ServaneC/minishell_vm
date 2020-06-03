/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 17:27:33 by schene            #+#    #+#             */
/*   Updated: 2020/06/03 13:22:29 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		echo_variable(char *s, t_data *data, char **ret, int i)
{
	char	*tmp;

	if (s[i + 1] == '?')
	{
		*ret = clean_ft_strjoin(*ret, ft_itoa(data->status));
		i += 1;
	}
	else
	{
		if (var_value(data->env, &s[i]) != NULL)
		{
			tmp = ft_strjoin(*ret, var_value(data->env, &s[i]));
			free(*ret);
			*ret = tmp;
		}
		while (s[++i] && ft_isalnum(s[i]))
			;
		i--;
	}
	return (i);
}

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
