/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floating_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 00:24:33 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/17 19:55:59 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "ft_printf.h"
#include "mantissa.h"
#include "ft_bignum.h"
#include "libft.h"
#include "exponent.h"

static char	*eval_exponent(unsigned long long num, int exponent, char *str)
{
	char	*tmp;

	tmp = (mtp(ft_strrev(str), g_exponent[exponent]));
	free(str);
	if (num & 0x8000000000000000ull)
	{
		str = ft_strjoin("-", tmp);
		free(tmp);
		tmp = str;
	}
	return (tmp);
}

char		*get_float(double d)
{
	int					i;
	char				*str;
	char				*tmp;
	unsigned long long	mask;
	unsigned long long	num;

	if (d == 0)
		return (ft_itoa(0));
	ft_memcpy(&num, &d, sizeof(double));
	str = ft_itoa(1);
	mask = 0x8000000000000ull;
	i = 0;
	while (mask > 0)
	{
		tmp = str;
		if (num & mask)
		{
			str = ft_bignum_add(str, g_mantissa[i]);
			free(tmp);
		}
		mask >>= 1;
		i++;
	}
	return (eval_exponent(num, ((num >> 52) & ~2048) - 1023, str));
}
