/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cx_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:09:56 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/10 17:03:42 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		cx_conversion(t_flags *flags, va_list *args)
{
	return (x_conversion(flags, args));
}
