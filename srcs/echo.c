/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 11:26:54 by schene            #+#    #+#             */
/*   Updated: 2020/05/30 15:16:56 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char			*variable_value(t_list *env, char *var)
{
	char	*name;
	int		len;
	int		len2;

	name = &var[1];
	len2 = 0;
	while (ft_isalnum(name[len2]))
		len2++;
	while (env)
	{
		len = (ft_strlen(env->content) -
			ft_strlen(ft_strchr(env->content, '=')));
		len = len2 > len ? len2 : len;
		if (ft_strncmp(env->content, name, len) == 0)
			return (ft_strchr(env->content, '=') + 1);
		env = env->next;
	}
	if (ft_isdigit(name[0]) && name[1])
		return (&name[1]);
	return (NULL);
}

static int		echo_variable(char *s, t_data *data, char **ret, int i)
{
	char	*str;
	char	*tmp;

	if (s[i + 1] == '?')
	{
		str = ft_itoa(data->status);
		tmp = ft_strjoin(*ret, str);
		free(str);
		free(*ret);
		*ret = tmp;
		i += 1;
	}
	else
	{
		if (variable_value(data->env, &s[i]) != NULL)
		{
			tmp = ft_strjoin(*ret, variable_value(data->env, &s[i]));
			free(*ret);
			*ret = tmp;
		}
		while (s[++i] && ft_isalnum(s[i]))
			;
		i--;
	}
	return (i);
}

static char		*echo_str_sgl(char *str, t_data *data)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	*s;

	i = -1;
	(void)data;
	ret = ft_strdup("\0");
	s = ft_strtrim(str, "\'");
	while (s[++i])
	{
		str = ft_substr(s, i, 1);
		tmp = ft_strjoin(ret, str);
		free(str);
		free(ret);
		ret = tmp;
		if (!s[i])
			break ;
	}
	free(s);
	return (ret);
}


static char		*echo_str(char *str, t_data *data)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	*s;

	i = -1;
	ret = ft_strdup("\0");
	if (str[0] != '\'')
	{
		s = ft_strtrim(str, "\"");
		while (s[++i])
		{
			if (s[i] == '$' && s[i +1] && (ft_isalnum(s[i + 1]) 
				|| s[i + 1] == '?'))
				i = echo_variable(s, data, &ret, i);
			else
			{
				str = ft_substr(s, i, 1);
				tmp = ft_strjoin(ret, str);
				free(str);
				free(ret);
				ret = tmp;
			}
			if (!s[i])
				break ;
		}
		free(s);
	}
	else
	{
		s = echo_str_sgl(str, data);
		tmp = ft_strjoin(ret, s);
		free(s);
		free(ret);
		ret = tmp;
	}
	return (ret);
}

void			builtin_echo(t_data *data)
{
	int		i;
	int		j;
	char	*to_print;
	char	*tmp;
	char	*str;
	char	**tab;

	i = 0;
	if (data->cmd[1] && (ft_strncmp(data->cmd[1], "-n", 3) == 0))
		i = 1;
	to_print = ft_strdup("\0");
	while (data->cmd[++i])
	{
		tab = tab_of_quotes(data->cmd[i]);
		j = -1;
		while (tab[++j])
		{
			//printf("tab[%d] = |%s|\n", j, tab[j]);
			str = echo_str(tab[j], data);
			//printf("str = |%s|\n", str);
			tmp = ft_strjoin(to_print, str);
			free(str);
			free(to_print);
			to_print = tmp;
		}
		str = ft_strdup(" ");
		tmp = ft_strjoin(to_print, str);
		free(str);
		free(to_print);
		to_print = tmp;
		ft_free(tab);
	}
	if (data->cmd[1] && (ft_strncmp(data->cmd[1], "-n", 3) == 0))
		ft_putstr(to_print);
	else
		ft_putendl_fd(to_print, 1);
	free(to_print);
}
