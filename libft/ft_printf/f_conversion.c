/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:36:25 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 19:56:16 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "ft_bignum.h"
#include "libft.h"

static int	print_float(t_flags *f, char *n)
{
	int		nbprint;
	int		dot;

	dot = ft_strichr(n, '.');
	nbprint = ft_putnstr_fd(n, dot == -1 ? ft_strlen(n) : (unsigned int)dot,
																		f->fd);
	if (f->f & F_HASH)
		nbprint += ft_putchar_fd('.', f->fd);
	if (f->precision > 0 && dot != -1)
		nbprint += ft_putnstr_fd(n + dot, f->precision + 1, f->fd);
	if (dot == -1 && f->f & F_HASH)
		nbprint += ft_putnchar_fd('0', f->precision, f->fd);
	return (nbprint);
}

static char	*createdotnum(int dot)
{
	char	*num;
	int		i;

	i = 1;
	num = malloc(dot + 2);
	num[0] = '.';
	num[dot] = '1';
	num[dot + 1] = '\0';
	while (i < dot)
		num[i++] = '0';
	return (ft_strrev(num));
}

static char	*round_bignum(int p, char *n)
{
	int			dot;
	char		*tmp;
	char		*num;

	dot = ft_strichr(n, '.');
	if (dot == -1)
		return (n);
	if (dot + p + 1 < (int)ft_strlen(n))
	{
		if (n[dot + p + 1] - '0' >= 5)
		{
			num = createdotnum(p);
			tmp = ft_bignum_add(num, ft_strrev(n));
			free(n);
			free(num);
			return (ft_strrev(tmp));
		}
	}
	return (n);
}

static int	handle_flags(t_flags *f, char *r, int nbprint, double d)
{
	if (f->f & F_MINUS)
	{
		if (f->f & F_PLUS && d >= 0)
			nbprint += ft_putchar_fd('+', f->fd);
		if (f->f & F_SPACE && !(f->f & F_PLUS) && d >= 0)
			nbprint += ft_putchar_fd(' ', f->fd);
		nbprint += print_float(f, r);
		if (f->f & F_WIDTH)
			while (nbprint < f->width)
				nbprint += ft_putchar_fd(f->f & F_ZERO ? '0' : ' ', f->fd);
	}
	else
	{
		if (f->f & F_WIDTH)
			while (nbprint + f->precision + LARGEST(ft_strichr(r, '.')
				+ 1, 0) + ((f->f & F_PLUS || f->f & F_SPACE) &&
				d >= 0 ? 1 : 0) < f->width)
				nbprint += ft_putchar_fd(f->f & F_ZERO ? '0' : ' ', f->fd);
		if (f->f & F_PLUS && d >= 0)
			nbprint += ft_putchar_fd('+', f->fd);
		if (f->f & F_SPACE && !(f->f & F_PLUS) && d >= 0)
			nbprint += ft_putchar_fd(' ', f->fd);
		nbprint += print_float(f, r);
	}
	return (nbprint);
}

int			f_conversion(t_flags *flags, va_list *args)
{
	double	d;
	char	*r;
	int		nbprint;

	nbprint = 0;
	d = va_arg(*args, double);
	if (!(flags->f & F_PRECISION))
		flags->precision = 6;
	r = round_bignum(flags->precision, get_float(d));
	nbprint += handle_flags(flags, r, nbprint, d);
	free(r);
	return (nbprint);
}
