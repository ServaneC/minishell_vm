/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_hx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:23:24 by lemarabe          #+#    #+#             */
/*   Updated: 2020/02/02 21:47:36 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		ft_printf_hexa_min(va_list *arg_list, t_convert *data)
{
	int				ret;
	unsigned int	nb;

	nb = va_arg(*arg_list, unsigned int);
	ret = ft_puthexa_min_convert(nb, data);
	return (ret);
}

int		ft_printf_hexa_maj(va_list *arg_list, t_convert *data)
{
	int				ret;
	unsigned int	nb;

	nb = va_arg(*arg_list, unsigned int);
	ret = ft_puthexa_maj_convert(nb, data);
	return (ret);
}

int		ft_puthexa_min_convert(unsigned int nb, t_convert *data)
{
	char	*result;
	int		len;
	int		w;

	result = ft_itoa_base_ux(nb, data, "0123456789abcdef");
	len = ft_strlen(result);
	w = ft_abs(data->width);
	while (!data->minus && w-- > len)
		write(1, " ", 1);
	ft_putstr_fd(result, 1);
	while (data->minus && w-- > len)
		write(1, " ", 1);
	free(result);
	if (ft_abs(data->width) > len)
		return (len + (ft_abs(data->width) - len));
	return (len);
}

int		ft_puthexa_maj_convert(unsigned int nb, t_convert *data)
{
	char	*result;
	int		len;
	int		w;

	result = ft_itoa_base_ux(nb, data, "0123456789ABCDEF");
	len = ft_strlen(result);
	w = ft_abs(data->width);
	while (!data->minus && w-- > len)
	{
		if (data->width < 0 && data->precis == -1)
			write(1, "0", 1);
		else
			write(1, " ", 1);
	}
	ft_putstr_fd(result, 1);
	while (data->minus && w-- > len)
		write(1, " ", 1);
	free(result);
	if (ft_abs(data->width) > len)
		return (len + (ft_abs(data->width) - len));
	return (len);
}
