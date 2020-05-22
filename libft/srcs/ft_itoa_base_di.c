/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_di.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 22:03:58 by lemarabe          #+#    #+#             */
/*   Updated: 2020/02/02 21:47:36 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int		get_size(int s_count, t_convert *data, int nbr)
{
	int	size;

	size = s_count;
	if (s_count < data->precis)
		size += (data->precis - s_count);
	if (data->width < 0 && data->precis < 0 && s_count < ft_abs(data->width))
		size += (ft_abs(data->width) - s_count);
	else if (data->plus || data->space || nbr < 0)
		size++;
	return (size);
}

static long		put_sign_and_p(char *str, int nbr, t_convert *data, int s_count)
{
	long	l;
	int		i;
	int		p;
	int		w;

	i = 0;
	l = (long)nbr;
	p = data->precis;
	w = ft_abs(data->width);
	if (nbr < 0)
	{
		l = -(long)nbr;
		str[i++] = '-';
	}
	else if (data->plus && nbr >= 0)
		str[i++] = '+';
	else if (data->space && nbr >= 0)
		str[i++] = ' ';
	while (p-- > s_count)
		str[i++] = '0';
	while (p < 0 && data->width < 0 && w-- > s_count)
		str[i++] = '0';
	return (l);
}

static int		nbr_len(int nbr, int base_len, t_convert *data)
{
	int		i;
	long	p;

	if (!data->precis && nbr == 0)
		return (0);
	if (nbr == 0)
		return (1);
	i = 0;
	p = (long)nbr;
	if (nbr < 0)
		p = -(long)nbr;
	while (p)
	{
		p = p / base_len;
		i++;
	}
	return (i);
}

static char		*print_nbr(char *str, int nbr, char *base, t_convert *data)
{
	int		i;
	int		s_count;
	int		base_len;
	int		size;
	long	l;

	s_count = nbr_len(nbr, ft_strlen(base), data);
	size = get_size(s_count, data, nbr);
	base_len = ft_strlen(base);
	l = put_sign_and_p(str, nbr, data, s_count);
	i = size - 1;
	if (l == 0 && data->precis)
		str[i] = '0';
	else if (l == 0 && !data->precis)
		str[i] = 0;
	while (l)
	{
		str[i] = base[l % base_len];
		l = l / base_len;
		i--;
	}
	str[size] = 0;
	return (str);
}

char			*ft_itoa_base_di(int nbr, t_convert *data, char *base)
{
	int		s_count;
	int		size;
	char	*str;

	s_count = nbr_len(nbr, ft_strlen(base), data);
	size = get_size(s_count, data, nbr);
	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	str = print_nbr(str, nbr, base, data);
	return (str);
}
