/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:05:09 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 20:01:02 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

static void	flag_characters(char **format, t_flags *flags)
{
	if (**format == '#')
		flags->f |= F_HASH;
	else if (**format == '0')
		flags->f |= F_ZERO;
	else if (**format == '-')
		flags->f |= F_MINUS;
	else if (**format == '+')
		flags->f |= F_PLUS;
	else if (**format == ' ')
		flags->f |= F_SPACE;
	else
		return ;
	(*format)++;
}

static void	field_width(char **format, t_flags *flags, va_list *args)
{
	if (**format == '*')
	{
		flags->f |= F_WIDTH;
		flags->width = va_arg(*args, int);
		(*format)++;
	}
	else
	{
		if (!ft_isdigit(**format))
			return ;
		flags->width = ft_atoi(*format);
		if (flags->width > 0 || **format == '0')
		{
			flags->f |= F_WIDTH;
			(*format) += ft_numlen(flags->width);
		}
	}
}

static void	precision(char **format, t_flags *flags, va_list *args)
{
	if (**format == '.')
	{
		flags->f |= F_PRECISION;
		if (*++(*format) == '*')
			flags->precision = va_arg(*args, int);
		else
			flags->precision = ft_atoi(*format);
		if (flags->precision > 0 || **format == '0')
			(*format) += ft_numlen(flags->precision);
	}
}

static void	length_modifier(char **format, t_flags *flags)
{
	if (**format == 'h' && *(*format + 1) == 'h')
		flags->f |= F_HH;
	else if (**format == 'h')
		flags->f |= F_H;
	else if (**format == 'l' && *(*format + 1) == 'l')
		flags->f |= F_LL;
	else if (**format == 'l')
		flags->f |= F_L;
	else if (**format == 'j')
		flags->f |= F_J;
	else if (**format == 'z')
		flags->f |= F_Z;
	else
		return ;
	if ((flags->f & F_HH) || (flags->f & F_LL))
		(*format) += 2;
	else
		(*format)++;
}

int			print_arg(int fd, char **format, va_list *args)
{
	t_flags	flags;

	if (**format == '%')
	{
		(*format)++;
		return ((int)ft_putchar_fd('%', fd));
	}
	ft_memset(&flags, 0, sizeof(t_flags));
	flags.fd = fd;
	while (**format && ft_strchr("#0+- ", **format))
		flag_characters(format, &flags);
	field_width(format, &flags, args);
	precision(format, &flags, args);
	while (**format && ft_strchr("hljz", **format))
		length_modifier(format, &flags);
	flags.conversion = **format;
	if (flags.conversion == '\0')
		return (error_conversion(&flags));
	(*format)++;
	if (args == NULL)
		return (0);
	return (do_conversion(&flags, args));
}
