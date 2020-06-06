/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:02:24 by schene            #+#    #+#             */
/*   Updated: 2020/06/06 15:35:01 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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