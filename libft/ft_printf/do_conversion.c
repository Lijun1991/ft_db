/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 21:57:40 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 19:12:47 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		do_conversion(t_flags *flags, va_list *args)
{
	const char	*lookup = "sSpdDioOuUxXcCbfF";
	int			(*conversions[18])(t_flags *flags, va_list *args);
	char		*r;

	conversions[0] = s_conversion;
	conversions[1] = ls_conversion;
	conversions[2] = p_conversion;
	conversions[3] = d_conversion;
	conversions[4] = ld_conversion;
	conversions[5] = i_conversion;
	conversions[6] = o_conversion;
	conversions[7] = lo_conversion;
	conversions[8] = u_conversion;
	conversions[9] = lu_conversion;
	conversions[10] = x_conversion;
	conversions[11] = cx_conversion;
	conversions[12] = c_conversion;
	conversions[13] = lc_conversion;
	conversions[14] = b_conversion;
	conversions[15] = f_conversion;
	conversions[16] = f_conversion;
	r = ft_strchr(lookup, flags->conversion);
	if (r == NULL)
		return (error_conversion(flags));
	return ((*conversions[r - lookup])(flags, args));
}
