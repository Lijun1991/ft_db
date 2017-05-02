/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 13:45:00 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 18:16:03 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

static int	read_args(int fd, char *format, va_list *args, int nbprint)
{
	char	*fmt;

	if ((fmt = ft_strchr(format, '%')) == NULL)
	{
		nbprint += ft_putstr_fd(format, fd);
		return (nbprint);
	}
	else
	{
		ft_putnstr_fd(format, fmt - format, fd);
		nbprint += fmt - format;
		fmt++;
		nbprint += print_arg(fd, &fmt, args);
		format = fmt;
	}
	return (read_args(fd, format, args, nbprint));
}

int			ft_printf(const char *format, ...)
{
	va_list		args;
	int			r;

	va_start(args, format);
	r = read_args(1, (char*)format, &args, 0);
	va_end(args);
	return (r);
}

int			ft_fprintf(int fd, const char *format, ...)
{
	va_list		args;
	int			r;

	va_start(args, format);
	r = read_args(fd, (char*)format, &args, 0);
	va_end(args);
	return (r);
}
