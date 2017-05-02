/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:05:40 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 19:48:31 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static int	print_p(t_flags *f, unsigned long long p, int n)
{
	if (f->f & F_MINUS)
	{
		n += ft_putstr_fd("0x", f->fd);
		if (f->f & F_PRECISION && f->precision > ft_unumlen_base(p, 16))
			n += ft_putnchar_fd('0', f->precision - ft_unumlen_base(p, 16),
																		f->fd);
		if (!(f->f & F_PRECISION && f->precision == 0 && p == 0))
			n += ft_putudigit_base_fd(p, 16, ft_itoc, f->fd);
		if (f->f & F_WIDTH && f->width > n)
			n += ft_putnchar_fd(' ', f->width - n, f->fd);
	}
	else
	{
		n += 2 + LARGEST(f->precision, ft_unumlen_base(p, 16));
		if (f->f & F_WIDTH && f->width > n)
			n += ft_putnchar_fd(' ', f->width - n, f->fd);
		ft_putstr_fd("0x", f->fd);
		if (f->f & F_PRECISION && f->precision > ft_unumlen_base(p, 16))
			ft_putnchar_fd('0', f->precision - ft_unumlen_base(p, 16), f->fd);
		if (!(f->f & F_PRECISION && f->precision == 0 && p == 0 && n--))
			ft_putudigit_base_fd(p, 16, ft_itoc, f->fd);
	}
	return (n);
}

int			p_conversion(t_flags *flags, va_list *args)
{
	unsigned long long	addr;

	addr = (unsigned long long)va_arg(*args, void *);
	if (flags->f & F_ZERO)
	{
		flags->f |= F_PRECISION;
		flags->precision = flags->width > 2 ? flags->width - 2 : 1;
		flags->f |= F_MINUS;
	}
	return (print_p(flags, addr, 0));
}
