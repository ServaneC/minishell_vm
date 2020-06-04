/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:30:08 by schene            #+#    #+#             */
/*   Updated: 2020/06/04 17:04:58 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int				check_var_name(char **str, t_data *data)
{
	int		i;
	char	*name;

	name = ft_substr(*str, 0,
		(ft_strlen(*str) - ft_strlen(ft_strchr(*str, '='))));
	i = -1;
	while (name[++i])
	{
		if (!(ft_isalnum(name[i])) && !(name[i] == '_'))
		{
			data->status = 1;
			ft_putstr_fd("minishell: export: invalid variable name: ", 2);
			ft_putendl_fd(name, 2);
			free(name);
			free(*str);
			return (-1);
		}
	}
	free(name);
	return (1);
}

static int		replace_ifexist(t_list *env, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	while (env)
	{
		if (ft_strncmp(env->content, str, i) == 0)
		{
			free(env->content);
			env->content = str;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void			builtin_export(t_data *data)
{
	t_list	*new;
	char	*str;
	int		ret;
	int		i;

	data->status = 0;
	if (data->cmd[1] == NULL)
		print_env(data);
	i = 0;
	while (data->cmd[++i])
	{
		if (ft_strchr(data->cmd[i], '=') != NULL)
		{
			str = rm_quotes_env(ft_strdup(data->cmd[i]));
			if (check_var_name(&str, data) == -1)
				break ;
			if ((ret = replace_ifexist(data->env, str)) == 0)
			{
				new = ft_lstnew(str);
				ft_lstadd_back(&data->env, new);
			}
			else if (ret == -1)
				ft_putendl_fd(strerror(errno), 2);
		}
	}
}
