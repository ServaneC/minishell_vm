/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 14:04:32 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 15:20:01 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void			free_block(t_list *to_free)
{
	free(to_free->content);
	to_free->content = NULL;
	free(to_free);
	to_free = NULL;
}

static t_list		*env_delete_elem(t_list *env, char *str)
{
	t_list	*tmp;
	t_list	*previous;

	if (env == NULL)
		return (NULL);
	previous = env;
	if (ft_strncmp(str, env->content, len_variable(env->content)) == 0)
	{
		env = env->next;
		free_block(previous);
		return (env);
	}
	tmp = previous->next;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->content, len_variable(tmp->content)) == 0)
		{
			previous->next = tmp->next;
			free_block(tmp);
			return (env);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (env);
}

void				builtin_unset(t_data *data)
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
