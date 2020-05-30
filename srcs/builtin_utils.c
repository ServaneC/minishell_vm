/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 17:27:33 by schene            #+#    #+#             */
/*   Updated: 2020/05/30 17:29:59 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		echo_variable(char *s, t_data *data, char **ret, int i)
{
	char	*tmp;

	if (s[i + 1] == '?')
	{
		*ret = clean_ft_strjoin(*ret, ft_itoa(data->status));
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
