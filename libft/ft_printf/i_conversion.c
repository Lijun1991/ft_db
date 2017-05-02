/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 01:07:44 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/10 16:55:47 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		i_conversion(t_flags *flags, va_list *args)
{
	return (d_conversion(flags, args));
}
