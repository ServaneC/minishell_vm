/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:30:08 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 14:09:37 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int				check_var_name(char **str, t_data *data)
{
	int		i;
	char	*name;

	name = ft_substr(*str, 0,
		(ft_strlen(*str) - ft_strlen(ft_strchr(*str, '='))));
	if (!name[0])
		return (-1);
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

static char			*removeplus(char *str)
{
	char	*start;
	char	*end;

	end = ft_strchr(str, '+');
	if (end == NULL)
		return (str);
	end = ft_substr(end, 1, ft_strlen(end - 1));
	start = ft_substr(str, 0, ft_strlen(str) - ft_strlen(end) - 1);
	free(str);
	str = ft_strjoin(start, end);
	free(start);
	free(end);
	return (str);
}

static int		replace_ifexist(t_list *env, char *str)
{
	int		i;
	int		len;
	int		a;
	char	*tmp;

	i = 0;
	a = 0;
	while (str[i] != '=')
		i++;
	if (str[i - 1] == '+')
		a = 1;
	i -= a;
	while (env)
	{
		len = len_variable(env->content);
		len = i > len ? i : len;
		if (ft_strncmp(env->content, str, len) == 0)
		{
			if (a)
			{
				tmp = ft_strjoin(env->content, &str[i + 2]);
				free(str);
				str = tmp;
			}
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
			{
				data->status = 1;
				break ;
			}
			if ((ret = replace_ifexist(data->env, str)) == 0)
			{
				str = removeplus(str);
				new = ft_lstnew(str);
				ft_lstadd_back(&data->env, new);
			}
			else if (ret == -1)
				ft_putendl_fd(strerror(errno), 2);
		}
	}
}

char			*rm_quotes_env(char *var)
{
	char	*name;
	char	*value;
	char	*ret;
	int		len;

	ret = ft_strdup(var);
	var = remove_quotes(var);
	len = ft_strncmp(ret, var, ft_strlen(var));
	free(ret);
	ret = NULL;
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