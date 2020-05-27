/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:30:08 by schene            #+#    #+#             */
/*   Updated: 2020/05/27 17:04:31 by schene           ###   ########.fr       */
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

void			builtin_export(t_data *data)
{
	t_list	*new;
	char	*str;
	int		ret;
	int		i;

	if (data->cmd[1] == NULL)
		print_env(data->env);
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
}
