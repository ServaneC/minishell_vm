/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:00:00 by schene            #+#    #+#             */
/*   Updated: 2020/06/15 13:26:02 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_list	*create_basic_env(void)
{
	char	cwd[MAX_PATH];
	t_list	*env;

	getcwd(cwd, MAX_PATH);
	env = ft_lstnew(clean_ft_strjoin(ft_strdup("PWD="), ft_strdup(cwd)));
	ft_lstadd_back(&env, ft_lstnew(ft_strdup("SHLVL=1")));
	return (env);
}

static void		increase_shlvl(t_list *env)
{
	char	*value;
	int		level;

	value = var_value(env, "$SHLVL");
	level = ft_atoi(value);
	value = ft_itoa(level + 1);
	replace_ifexist(env, ft_strjoin("SHLVL=", value));
	free(value);
}

t_list			*create_env(char **env)
{
	int		i;
	char	*str;
	t_list	*my_env;
	t_list	*next;

	if (!env[0])
		return (create_basic_env());
	str = ft_strdup(env[0]);
	my_env = ft_lstnew(str);
	i = 0;
	while (env[++i])
	{
		str = ft_strdup(env[i]);
		next = ft_lstnew(str);
		ft_lstadd_back(&my_env, next);
	}
	increase_shlvl(my_env);
	return (my_env);
}

static void		print_elem(void *str)
{
	if (ft_strchr(str, '=') != NULL)
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
