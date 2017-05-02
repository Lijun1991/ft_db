/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:20:20 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/17 18:35:11 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_bignum.h"

static char	addchars(char n1, char n2, char *reminder)
{
	int		a;
	int		b;
	int		r;

	a = n1 - '0';
	b = n2 - '0';
	r = a + b + (*reminder - '0');
	*reminder = r > 9 ? '1' : '0';
	r = r % 10;
	return (r + '0');
}

static void	reminder(const char *str1, const char *str2, char *result)
{
	char	reminder;

	reminder = '0';
	while (*str1 && *str2)
		if (*str1 == '.' || *str2 == '.')
		{
			str1 += *str1 == '.' ? 1 : 0;
			str2 += *str2 == '.' ? 1 : 0;
			*result++ = '.';
		}
		else
			*result++ = addchars(*str1++, *str2++, &reminder);
	while (*str1)
		*result++ = addchars(*str1++, '0', &reminder);
	while (*str2)
		*result++ = addchars(*str2++, '0', &reminder);
	if (reminder == '1')
		*result = '1';
}

char		*ft_bignum_add(const char *str1, const char *str2)
{
	char	*result;
	char	*r;
	int		d1;
	int		d2;

	result = ft_strnew(ft_strlen(str1) + ft_strlen(str2) + 2 + 1);
	r = result;
	d1 = ft_strichr(str1, '.');
	d2 = ft_strichr(str2, '.');
	if (d1 > d2)
	{
		ft_strncpy(result, str1, d1 - d2);
		result += (d1 - d2);
		str1 += (d1 - d2);
	}
	else if (d1 < d2)
	{
		ft_strncpy(result, str2, d2 - d1);
		result += (d2 - d1);
		str2 += (d2 - d1);
	}
	reminder(str1, str2, result);
	return (r);
}
