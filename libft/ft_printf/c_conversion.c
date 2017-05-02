/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:10:20 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 19:48:51 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>
#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

static int	handle_c(t_flags *f, unsigned char c)
{
	int		nbprint;

	nbprint = 0;
	if (f->f & F_MINUS)
	{
		nbprint += write(f->fd, &c, 1);
		if (f->f & F_WIDTH && f->width > nbprint)
			nbprint += ft_putnchar_fd(f->f & F_ZERO ? '0' : ' ', f->width -
					nbprint, f->fd);
	}
	else
	{
		if (f->f & F_WIDTH && f->width > nbprint + 1)
			nbprint += ft_putnchar_fd(f->f & F_ZERO ? '0' : ' ', f->width -
					(nbprint + 1), f->fd);
		nbprint += write(f->fd, &c, 1);
	}
	return (nbprint);
}

static int	handle_wc(t_flags *f, wchar_t wc)
{
	int		nbprint;
	int		size;
	char	mb[4];

	size = ft_wctomb(mb, wc);
	nbprint = 0;
	if (f->f & F_MINUS)
	{
		nbprint += write(f->fd, mb, size);
		if (f->f & F_WIDTH && f->width > nbprint + 1)
			nbprint += ft_putnchar_fd(' ', f->width - nbprint + 1, f->fd);
	}
	else
	{
		if (f->f & F_WIDTH && f->width > nbprint + 1)
			nbprint += ft_putnchar_fd(' ', f->width - nbprint + 1, f->fd);
		nbprint += write(f->fd, mb, size);
	}
	return (nbprint);
}

int			c_conversion(t_flags *flags, va_list *args)
{
	int		nbprint;

	nbprint = 0;
	if (flags->f & F_L)
	{
		nbprint += handle_wc(flags, va_arg(*args, wchar_t));
	}
	else
	{
		nbprint += handle_c(flags, (unsigned char)va_arg(*args, int));
	}
	return (nbprint);
}
