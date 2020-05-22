/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:22:55 by lemarabe          #+#    #+#             */
/*   Updated: 2020/02/20 13:43:20 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../include/libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_convert
{
	int			minus;
	int			plus;
	int			space;
	int			width;
	int			precis;
}				t_convert;
int				ft_printf_char(va_list *arg_list, t_convert *data);
int				ft_printf_str(va_list *arg_list, t_convert *data);
int				ft_printf_adr(va_list *arg_list, t_convert *data);
int				ft_printf_nbr(va_list *arg_list, t_convert *data);
int				ft_printf_nbr_u(va_list *arg_list, t_convert *data);
int				ft_printf_hexa_min(va_list *arg_list, t_convert *data);
int				ft_printf_hexa_maj(va_list *arg_list, t_convert *data);
int				ft_printf_modulo(va_list *arg_list, t_convert *data);
int				ft_putchar_convert(char c, t_convert *data);
int				ft_putstr_convert(char *str, t_convert *data);
int				ft_putaddress_convert(unsigned long ptr, t_convert *data);
int				ft_putnbr_convert(int n, t_convert *data);
int				ft_putunsigned_convert(unsigned int n, t_convert *data);
int				ft_puthexa_min_convert(unsigned int nb, t_convert *data);
int				ft_puthexa_maj_convert(unsigned int nb, t_convert *data);
char			*ft_itoa_base_di(int nbr, t_convert *data, char *base);
char			*ft_itoa_base_ux(unsigned long nbr, t_convert *data,
				char *base);
int				ft_atoi_from(char *str, int i);
int				ft_abs(int nb);
void			reset_converts(t_convert *data);
void			set_converts(char *sgmt, t_convert *data, va_list *arg_list);
int				ft_printf(char *format, ...);

#endif
