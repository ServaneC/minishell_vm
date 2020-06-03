/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:30:08 by schene            #+#    #+#             */
/*   Updated: 2020/06/03 17:42:43 by schene           ###   ########.fr       */
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

static char		*rm_quotes_env(char *var)
{
	char	*name;
	char	*value;
	char	*ret;
	int		len;

	ret = ft_strdup(var);
	var = remove_quotes(var);
	len = ft_strncmp(ret, var, ft_strlen(var));
	free(ret);
	if (len == 0)
	{
		len = ft_strlen(var) - ft_strlen(ft_strchr(var, '='));
		name = ft_substr(var, 0, ++len);
		value = ft_strdup(&var[len]);
		value = remove_quotes(value);
		ret = ft_strjoin(name, value);
		free(value);
		free(var);
		free(name);
		return (ret);
	}
	return (var);
}

void			builtin_export(t_data *data)
{
	t_list	*new;
	char	*str;
	int		ret;
	int		i;

	if (data->cmd[1] == NULL)
		print_env(data);
	i = 0;
	while (data->cmd[++i])
	{
		if (ft_strchr(data->cmd[i], '=') != NULL)
		{
			str = ft_strdup(data->cmd[i]);
			str = rm_quotes_env(str);
			if ((ret = replace_ifexist(data->env, str)) == 0)
			{
				new = ft_lstnew(str);
				ft_lstadd_back(&data->env, new);
			}
			else if (ret == -1)
				ft_putendl_fd(strerror(errno), 2);
		}
	}
	data->status = 0;
}
