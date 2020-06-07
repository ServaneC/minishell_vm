/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 14:04:32 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 14:05:39 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_list		*env_delete_elem(t_list *env, char *str)
{
	t_list	*tmp;
	t_list	*previous;
	int		len;

	if (env == NULL)
		return (NULL);
	previous = env;
	len = len_variable(env->content);
	if (ft_strncmp(str, env->content, len) == 0)
	{
		env = env->next;
		free(previous->content);
		previous->content = NULL;
		free(previous);
		previous = NULL;
		return (env);
	}
	tmp = previous->next;
	while (tmp)
	{
		len = len_variable(tmp->content);
		if (ft_strncmp(str, tmp->content, len) == 0)
		{
			previous->next = tmp->next;
			free(tmp->content);
			tmp->content = NULL;
			free(tmp);
			tmp = NULL;
			return (env);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (env);
}

void			builtin_unset(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (data->cmd[1] == NULL)
		ft_putendl_fd("unset: not enough arguments", 2);
	while (data->cmd[++i])
	{
		tmp = ft_strdup(data->cmd[i]);
		env_delete_elem(data->env, tmp);
		free(tmp);
	}
	data->status = 0;
}