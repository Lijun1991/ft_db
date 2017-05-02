/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lu_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:09:07 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/13 20:45:55 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		lu_conversion(t_flags *flags, va_list *args)
{
	flags->f |= F_L;
	flags->f &= ~(F_HH | F_H | F_LL | F_J | F_Z);
	return (u_conversion(flags, args));
}
