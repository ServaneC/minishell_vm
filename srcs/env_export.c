/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:30:08 by schene            #+#    #+#             */
/*   Updated: 2020/06/15 13:16:46 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int			error_name(char **str, char **name, t_data *data)
{
	ft_putstr_fd("minishell: export: \"", 2);
	ft_putstr_fd(*name, 2);
	ft_putendl_fd("\" : not an identifier", 2);
	free(*str);
	free(*name);
	data->status = 1;
	return (-1);
}

static int			check_var_name(char **str, t_data *data)
{
	int		i;
	char	*name;

	name = ft_substr(*str, 0,
		(ft_strlen(*str) - ft_strlen(ft_strchr(*str, '='))));
	if (!name[0] || ft_isdigit(name[0]))
		return (error_name(str, &name, data));
	i = -1;
	while (name[++i])
	{
		if (!(ft_isalnum(name[i])) && !(name[i] == '_'))
		{
			if (name[i] == '+' && !name[i + 1])
			{
				free(name);
				return (1);
			}
			data->status = 1;
			return (error_name(str, &name, data));
		}
	}
	free(name);
	return (1);
}

static void			append_var(char **str, t_list *env, int i)
{
	char	*s;
	char	*tmp;

	s = *str;
	tmp = ft_strjoin(env->content, &s[i + 2]);
	free(*str);
	*str = tmp;
}

int					replace_ifexist(t_list *env, char *str)
{
	int		i;
	int		len;
	int		a;

	i = len_variable(str);
	a = str[i - 1] == '+' ? 1 : 0;
	i -= a;
	while (env)
	{
		len = i > len_variable(env->content) ? i : len_variable(env->content);
		if (ft_strncmp(env->content, str, len) == 0)
		{
			if (a)
				append_var(&str, env, i);
			free(env->content);
			env->content = str;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void				builtin_export(t_data *data)
{
	t_list	*new;
	char	*str;
	int		ret;
	int		i;

	data->status = 0;
	if (data->cmd[1] == NULL)
		print_export(data);
	i = 0;
	while (data->cmd[++i])
	{
		str = ft_strdup(data->cmd[i]);
		if (check_var_name(&str, data) == -1)
			break ;
		if ((ret = replace_ifexist(data->env, str)) == 0)
		{
			new = ft_lstnew(removeplus(str));
			ft_lstadd_back(&data->env, new);
		}
		else if (ret == -1)
			ft_putendl_fd(strerror(errno), 2);
	}
}
