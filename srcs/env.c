/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/06/06 16:06:12 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list			*create_env(char **env)
{
	int		i;
	char	*str;
	t_list	*my_env;
	t_list	*next;

	str = ft_strdup(env[0]);
	my_env = ft_lstnew(str);
	i = 0;
	while (env[++i])
	{
		str = ft_strdup(env[i]);
		next = ft_lstnew(str);
		ft_lstadd_back(&my_env, next);
	}
	return (my_env);
}

int					len_variable(void *str)
{
	int		len;
	char	*s;

	s = (char *)str;
	len = 0;
	while (s[len] != '=')
		len++;
	return (len);
}

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

char			**convert_env_to_tab(t_list *env)
{
	char	**tab;
	int		i;
	int		len;

	len = ft_lstsize(env);
	if (!(tab = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len && env)
	{
		tab[i] = env->content;
		tab[i + 1] = NULL;
		env = env->next;
	}
	return (tab);
}
