/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 14:41:48 by schene           ###   ########.fr       */
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

int				len_variable(void *str)
{
	int		len;
	char	*s;

	s = (char *)str;
	len = 0;
	while (s[len] != '=')
		len++;
	return (len);
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

static void		print_elem(void *str)
{
	ft_putendl_fd((char *)str, 1);
}

void			print_env(t_data *data)
{
	data->status = 0;
	if (data->cmd[1])
	{
		ft_putendl_fd("minishell: env: the env command accept no arguments", 2);
		data->status = 1;
	}
	else
		ft_lstiter(data->env, &print_elem);
}
