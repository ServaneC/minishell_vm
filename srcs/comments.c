/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 15:42:38 by schene            #+#    #+#             */
/*   Updated: 2020/06/12 17:16:30 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_occur_before(char *str, int i, int c)
{
	int	count;

	count = 0;
	while (--i >= 0)
	{
		if (str[i] == c && (!i || str[i - 1] != '\\'))
			count++;
	}
	return (count);
}

static int	count_occur_after(char *str, int i, int c)
{
	int count;

	count = 0;
	while (str[++i])
	{
		if (str[i] == c && (!i || str[i - 1] != '\\'))
			count++;
	}
	return (count);
}

static int	between_quotes(char *str, int i)
{
	int qu_left;
	int qu_right;

	qu_left = count_occur_before(str, i, '\'');
	qu_right = count_occur_after(str, i, '\'');
	if (qu_right % 2 || qu_left % 2)
		return (1);
	qu_left = count_occur_before(str, i, '\"');
	qu_right = count_occur_after(str, i, '\"');
	if (qu_right % 2 || qu_left % 2)
		return (2);
	return (0);
}

char		*contains_comment(char *str)
{
	char	*ret;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '#' && is_meta(str, i) && !between_quotes(str, i) &&
			(!str[i - 1] || ft_isspace(str[i - 1])))
			break ;
	}
	ret = ft_substr(str, 0, i);
	return (ret);
}
