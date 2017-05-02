/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:58:26 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 19:45:53 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	handle_width(t_flags *flags, int size, char *s)
{
	int		nbprint;

	nbprint = 0;
	if (flags->f & F_MINUS)
	{
		nbprint += ft_putnstr_fd(s, size, flags->fd);
		while (flags->width - size > 0)
		{
			nbprint += ft_putchar_fd(flags->f & F_ZERO ? '0' : ' ', flags->fd);
			flags->width--;
		}
	}
	else
	{
		while (flags->width - size > 0)
		{
			nbprint += ft_putchar_fd(flags->f & F_ZERO ? '0' : ' ', flags->fd);
			flags->width--;
		}
		nbprint += ft_putnstr_fd(s, size, flags->fd);
	}
	return (nbprint);
}

int			handle_string(t_flags *flags, char *s)
{
	int		len;
	int		size;
	int		nbprint;

	nbprint = 0;
	len = ft_strlen(s);
	if (flags->f & F_PRECISION && flags->conversion == 's')
		size = flags->precision < len ? flags->precision : len;
	else
		size = len;
	if (flags->f & F_WIDTH && flags->width > size)
		nbprint += handle_width(flags, size, s);
	else
		nbprint += ft_putnstr_fd(s, size, flags->fd);
	return (nbprint);
}
