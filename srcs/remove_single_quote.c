/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:02:24 by schene            #+#    #+#             */
/*   Updated: 2020/05/27 15:37:43 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		count_quotes(char *str, char c)
{
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	while (str[++i])
		if (str[i] == c)
			nb++;
	return (nb);
}

static char		*new_strquote(char *str, char c)
{
	char	*start;
	int		len;
	char	*ret;
	char	*ptr;

	ptr = ft_strrchr(str, c);
	len = ft_strlen(str) - ft_strlen(ptr);
	start = ft_substr(str, 0, len);
	ret = ft_strjoin(start, ptr + 1);
	free(start);
	free(str);
	return (ret);
}

char			*rm_sgl_quote(char *str)
{
	char	q;

	q = '\"';
	if (ft_strchr(str, q))
		if (count_quotes(str, q) % 2)
			str = new_strquote(str, q);
	q = '\'';
	if (ft_strchr(str, q))
		if (count_quotes(str, q) % 2)
			str = new_strquote(str, q);
	return (str);
}
