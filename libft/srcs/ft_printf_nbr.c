/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:23:46 by lemarabe          #+#    #+#             */
/*   Updated: 2020/02/02 21:47:36 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf_nbr(va_list *arg_list, t_convert *data)
{
	int	nb;
	int	ret;

	nb = va_arg(*arg_list, int);
	ret = ft_putnbr_convert(nb, data);
	return (ret);
}

int	ft_putnbr_convert(int n, t_convert *data)
{
	char	*result;
	int		len;
	int		w;

	result = ft_itoa_base_di(n, data, "0123456789");
	len = ft_strlen(result);
	w = ft_abs(data->width);
	while (!data->minus && w-- > len)
		write(1, " ", 1);
	ft_putstr_fd(result, 1);
	while (data->minus && w-- > len)
		write(1, " ", 1);
	free(result);
	if (ft_abs(data->width) > len)
		return (len + (ft_abs(data->width)) - len);
	return (len);
}
