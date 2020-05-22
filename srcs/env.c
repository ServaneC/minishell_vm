/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/05/22 16:00:18 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void		print_elem(void *str)
{
	ft_putendl_fd((char *)str, 1);
}

void			print_env(t_list *env)
{
	ft_lstiter(env, &print_elem);
}

t_list			*create_env(char **env)
{
	int		i;
	t_list	*my_env;
	t_list	*next;

	my_env = ft_lstnew(env[0]);
	i = 0;
	while (env[++i])
	{
		next = ft_lstnew(env[i]);
		ft_lstadd_back(&my_env, next);
	}
	return (my_env);
}

int				replace_ifexist(t_list *env, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	while (env->next)
	{
		if (ft_strncmp(env->content, str, i) == 0)
		{
			env->content = str;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void			builtin_export(char **cmd, t_list *env)
{
	t_list	*new;
	char	*str;
	int		ret;
	int		i;

	if (cmd[1] == NULL)
		print_env(env);
	i = 0;
	while (cmd[++i])
	{
		str = ft_strdup(cmd[i]);
		if (ft_strchr(str, '=') != NULL)
		{
			if ((ret = replace_ifexist(env, str)) == 0)
			{
				new = ft_lstnew(str);
				ft_lstadd_back(&env, new);
			}
			else if (ret == -1)
				ft_putendl_fd(strerror(errno), 2);
		}
	}
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

t_list			*env_delete_elem(t_list *env, char *str)
{
	t_list	*tmp;
	int		len;

	if (env == NULL)
		return (NULL);
	len = len_variable(env->content);
	if (ft_strncmp(str, env->content, len) == 0)
	{
		tmp = env->next;
		free(env);
		return (tmp);
	}
	env->next = env_delete_elem(env->next, str);
	return (env);
}

void			builtin_unset(char **cmd, t_list *env)
{
	int	i;

	i = 0;
	if (cmd[1] == NULL)
		ft_putendl_fd("unset: not enough arguments", 2);
	while (cmd[++i])
		env_delete_elem(env, ft_strdup(cmd[i]));
}
