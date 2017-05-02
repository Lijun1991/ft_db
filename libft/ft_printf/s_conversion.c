/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:34:09 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/12 17:27:07 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <wchar.h>
#include "ft_printf.h"
#include "libft.h"

int		s_conversion(t_flags *flags, va_list *args)
{
	char	*arg;
	wchar_t	*wcstr;

	if (flags->f & F_L)
	{
		wcstr = va_arg(*args, wchar_t *);
		if (wcstr == NULL)
			wcstr = L"(null)";
		return ((int)handle_wcstr(flags, wcstr));
	}
	else
	{
		arg = va_arg(*args, char *);
		if (arg == NULL)
			arg = "(null)";
		return (handle_string(flags, arg));
	}
}
