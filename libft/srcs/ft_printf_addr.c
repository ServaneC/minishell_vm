/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:22:48 by lemarabe          #+#    #+#             */
/*   Updated: 2020/02/02 21:47:36 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int			ft_printf_adr(va_list *arg_list, t_convert *data)
{
	unsigned long	ptr;
	int				ret;

	ptr = va_arg(*arg_list, unsigned long);
	ret = ft_putaddress_convert(ptr, data);
	return (ret);
}

static char	*put_right_value(char *addr)
{
	int		len;
	int		i;
	int		j;
	char	*new;

	len = ft_strlen(addr);
	if (!(new = malloc(sizeof(char) * (len + 3))))
		return (NULL);
	new[0] = '0';
	new[1] = 'x';
	i = 2;
	j = 0;
	while (j < len)
		new[i++] = addr[j++];
	new[i] = 0;
	free(addr);
	return (new);
}

int			ft_putaddress_convert(unsigned long ptr, t_convert *data)
{
	char	*adr;
	int		len;
	int		w;

	data->plus = 0;
	data->space = 0;
	if (data->precis)
		data->precis = -1;
	adr = put_right_value(ft_itoa_base_ux(ptr, data, "0123456789abcdef"));
	len = ft_strlen(adr);
	w = ft_abs(data->width);
	while (!data->minus && w-- > len)
		write(1, " ", 1);
	ft_putstr_fd(adr, 1);
	while (data->minus && w-- > len)
		write(1, " ", 1);
	free(adr);
	if (data->width > len)
		return (len + (ft_abs(data->width) - len));
	return (len);
}
