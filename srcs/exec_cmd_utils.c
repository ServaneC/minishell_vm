/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:57:40 by schene            #+#    #+#             */
/*   Updated: 2020/06/18 15:04:39 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			try_path(char *path)
{
	DIR			*dir;
	int			ret;
	struct stat *buf;

	if (!(buf = (struct stat *)malloc(sizeof(struct stat))))
		return (-1);
	ret = lstat(path, buf);
	free(buf);
	buf = NULL;
	if (ret == 0)
	{
		if ((dir = opendir(path)) == NULL)
			return (ret);
		closedir(dir);
		errno = 21;
		return (-1);
	}
	return (ret);
}

void		print_exec_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (errno != 2)
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd("command not found", 2);
}

char		*var_value(t_list *env, char *var)
{
	char	*name;
	char	*test;
	int		len;
	int		len2;

	name = &var[1];
	len2 = len_variable(name);
	while (env)
	{
		len = (ft_strlen(env->content) -
			ft_strlen(ft_strchr(env->content, '=')));
		len = len2 > len ? len2 : len;
		if (ft_strncmp(env->content, name, len) == 0)
		{
			test = ft_strchr(env->content, '=');
			if (ft_strlen(test) < 2)
				return (NULL);
			return (test + 1);
		}
		env = env->next;
	}
	if (ft_isdigit(name[0]) && name[1])
		return (&name[1]);
	return (NULL);
}

t_data		*init_data(char **main_env)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->env = create_env(main_env);
	data->cmd = NULL;
	data->output = 0;
	data->line = NULL;
	data->multi = NULL;
	data->pipe = NULL;
	data->dir = ft_strdup(var_value(data->env, "$PWD"));
	data->status = 0;
	data->input = 0;
	return (data);
}
