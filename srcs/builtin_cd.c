/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:40:08 by schene            #+#    #+#             */
/*   Updated: 2020/06/05 12:39:03 by schene           ###   ########.fr       */
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

void			change_dir(t_data *data)
{
	char			old_pwd[MAX_PATH];
	char			pwd[MAX_PATH];
	struct  stat	*buf;
	char			*str;
	

	if (getcwd(old_pwd, MAX_PATH) == NULL)
	{
		str = ft_strdup("getcwd");
		ft_error(&str);
	}
	buf = (struct stat *)malloc(sizeof(struct stat));
	if (lstat(data->cmd[1], buf) == 0)
	{
		if (chdir(data->cmd[1]) == 0)
		{
			getcwd(pwd, MAX_PATH);
			change_value(data->env, "PWD", pwd);
			change_value(data->env, "OLDPWD", old_pwd);
		}
	}
	else
	{
		str = ft_strdup("cd");
		ft_error(&str);
		data->status = 1;
	}
	free (buf);
}

void			builtin_cd(t_data *data)
{
	char	*str;

	data->status = 0;
	if (!data->cmd[1])
		data->cmd[1] = ft_strdup(var_value(data->env, "$HOME"));
	if (data->cmd[2])
	{
		ft_putendl_fd("minishell: cd: too much arguments", 2);
		data->status = 1;
		return ;
	}
	str = echo_str(data->cmd[1], data);
	free(data->cmd[1]);
	data->cmd[1] = str;
	if (data->cmd[1][0] == '~')
		data->cmd[1] = ft_strjoin(var_value(data->env, "$HOME"),
				&data->cmd[1][1]);
	change_dir(data);
}
