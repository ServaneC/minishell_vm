/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:40:08 by schene            #+#    #+#             */
/*   Updated: 2020/06/03 18:06:56 by schene           ###   ########.fr       */
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
	char	old_pwd[MAX_PATH];
	char	pwd[MAX_PATH];

	getcwd(old_pwd, MAX_PATH);
	if (chdir(data->cmd[1]) == 0)
	{
		getcwd(pwd, MAX_PATH);
		change_value(data->env, "PWD", pwd);
		change_value(data->env, "OLDPWD", old_pwd);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		data->status = 1;
	}
}

void			builtin_cd(t_data *data)
{
	data->status = 0;
	if (!data->cmd[1])
	{
		ft_putendl_fd("minishell: cd: no arguments", 2);
		return ;
	}
	if (data->cmd[2])
	{
		ft_putendl_fd("minishell: cd: too much arguments", 2);
		data->status = 1;
		return ;
	}
	if (data->cmd[1][0] == '$')
	{
		if (var_value(data->env, data->cmd[1]) == NULL)
			data->cmd[1] = "$HOME";
		data->cmd[1] = var_value(data->env, data->cmd[1]);
	}
	if (data->cmd[1][0] == '~')
		data->cmd[1] = ft_strjoin(var_value(data->env, "$HOME"),
				&data->cmd[1][1]);
	change_dir(data);
}
