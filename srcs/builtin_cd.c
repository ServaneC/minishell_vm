/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:40:08 by schene            #+#    #+#             */
/*   Updated: 2020/06/05 18:11:02 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		change_value(t_list *env, char *name, char *newvalue)
{
	char	*tmp;
	char	*new;

	tmp = ft_strjoin(name, "=");
	new = ft_strjoin(tmp, newvalue);
	free(tmp);
	while (env->next)
	{
		if (ft_strncmp(env->content, name, ft_strlen(name)) == 0)
		{
			free(env->content);
			env->content = new;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void			change_dir(t_data *data, char *path)
{
	char			old_pwd[MAX_PATH];
	char			pwd[MAX_PATH];
	struct stat		*buf;
	char			*str;
	
	if (getcwd(old_pwd, MAX_PATH) == NULL && data->cmd[1][0] == '.' && !data->cmd[1][1])
	{
		str = ft_strdup("cd");
		ft_error(&str);
		change_value(data->env, "OLDPWD", var_value(data->env, "$PWD"));
		str = ft_strjoin(var_value(data->env, "$PWD"), "/.");
		change_value(data->env, "PWD", str);
		free(str);
		return ;
	}
	buf = (struct stat *)malloc(sizeof(struct stat));
	if (lstat(path, buf) == 0)
	{
		if (chdir(path) == 0)
		{
			getcwd(pwd, MAX_PATH);
			change_value(data->env, "PWD", pwd);
			free(data->dir);
			data->dir = ft_strdup(pwd);
			change_value(data->env, "OLDPWD", old_pwd);
		}
	}
	else
	{
		str = ft_strdup("cd");
		ft_error(&str);
		data->status = 1;
	}
	free(buf);
}

void			builtin_cd(t_data *data)
{
	char	*str;
	char	*tmp;

	data->status = 0;
	tmp = NULL;
	if (!data->cmd[1])
		str = ft_strdup(var_value(data->env, "$HOME"));
	else if (data->cmd[2])
	{
		ft_putendl_fd("minishell: cd: too much arguments", 2);
		data->status = 1;
		return ;
	}
	else
	{
		str = echo_str(data->cmd[1], data);
		if (str[0] == '~')
		{
			tmp = ft_strjoin(var_value(data->env, "$HOME"), &str[1]);
			free(str);
			str = tmp;
		}
	}
	change_dir(data, str);
	free(str);
}
