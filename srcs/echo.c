/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 11:26:54 by schene            #+#    #+#             */
/*   Updated: 2020/06/07 16:53:11 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int		next_s(t_data *data, char *cmd, int m)
{
	int		ret;
	char	*str;

	ret = 0;
	str = echo_str(cmd, data, m);
	if (str[0] && ft_strncmp(str, " ", ft_strlen(str) != 0))
		ret++;
	free(str);
	return (ret);
}

static void		fill_to_print(t_data *data, char **to_p, int i)
{
	int		j;
	char	*str;
	char	**tab;

	*to_p = ft_strdup("\0");
	while (data->cmd[++i])
	{
		tab = tab_of_quotes(data->cmd[i]);
		j = -1;
		while (tab[++j])
		{
			str = echo_str(tab[j], data, 0);
			*to_p = clean_ft_strjoin(*to_p, str);
		}
		if (data->cmd[i + 1] && next_s(data, data->cmd[i + 1], 0) && *to_p[0])
			*to_p = clean_ft_strjoin(*to_p, ft_strdup(" "));
		ft_free(tab);
	}
}

void			builtin_echo(t_data *data)
{
	int		i;
	int		n;
	char	*to_print;

	i = 0;
	n = 0;
	if (data->cmd[1] && (ft_strncmp(data->cmd[1], "-n", 3) == 0))
	{
		n = 1;
		i = 1;
		while (ft_strncmp(data->cmd[i], "-n", 3) == 0)
			i++;
		i--;
	}
	fill_to_print(data, &to_print, i);
	data->status = 0;
	ft_putstr(to_print);
	if (n == 0)
		ft_putchar_fd('\n', 1);
	free(to_print);
}
