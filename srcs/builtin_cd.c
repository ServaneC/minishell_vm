/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:40:08 by schene            #+#    #+#             */
/*   Updated: 2020/05/27 15:44:42 by schene           ###   ########.fr       */
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

void			builtin_cd(char *path, t_list *env)
{
	char	old_pwd[MAX_PATH];
	char	pwd[MAX_PATH];

	getcwd(old_pwd, MAX_PATH);
	if (path == NULL || path[0] == '$')
	{
		if (path == NULL || variable_value(env, path) == NULL)
			path = "$HOME";
		path = variable_value(env, path);
	}
	if (path[0] == '~')
		path = ft_strjoin(variable_value(env, "$HOME"), &path[1]);
	if (chdir(path) == 0)
	{
		getcwd(pwd, MAX_PATH);
		change_value(env, "PWD", pwd);
		change_value(env, "OLDPWD", old_pwd);
	}
	else
		ft_putendl_fd(strerror(errno), 2);
}
