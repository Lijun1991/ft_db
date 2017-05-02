/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lo_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:08:30 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/13 20:46:24 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		lo_conversion(t_flags *flags, va_list *args)
{
	flags->f |= F_L;
	flags->f &= ~(F_HH | F_H | F_LL | F_J | F_Z);
	return (o_conversion(flags, args));
}
