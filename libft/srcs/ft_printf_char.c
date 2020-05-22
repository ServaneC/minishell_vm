/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:23:12 by lemarabe          #+#    #+#             */
/*   Updated: 2020/02/02 21:47:36 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		ft_printf_char(va_list *arg_list, t_convert *data)
{
	char	c;
	int		ret;

	c = va_arg(*arg_list, int);
	ret = ft_putchar_convert(c, data);
	return (ret);
}

int		ft_putchar_convert(char c, t_convert *data)
{
	int	w;
	int	count;

	w = data->width;
	count = 0;
	while (!data->minus && w-- > 1)
	{
		write(1, " ", 1);
		count++;
	}
	ft_putchar_fd(c, 1);
	while (data->minus && w-- > 1)
	{
		write(1, " ", 1);
		count++;
	}
	return (count + 1);
}

int		ft_printf_modulo(va_list *arg_list, t_convert *data)
{
	int w;

	(void)arg_list;
	w = ft_abs(data->width);
	while (!data->minus && w-- > 1)
	{
		if (data->width < 0)
			write(1, "0", 1);
		else
			write(1, " ", 1);
	}
	ft_putchar_fd('%', 1);
	while (data->minus && w-- > 1)
		write(1, " ", 1);
	if (ft_abs(data->width) > 1)
		return (ft_abs(data->width));
	return (1);
}
