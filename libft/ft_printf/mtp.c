/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:08:45 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/27 02:18:31 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "ft_bignum.h"
#include "libft.h"

static char	*shiftdot(const char *n1, int by)
{
	char	*nodot;
	int		i;
	int		j;
	int		dot;

	dot = -1;
	nodot = malloc(ft_strlen(n1) + by + 1);
	ft_memset(nodot, 0, ft_strlen(n1) + by + 1);
	i = 0;
	j = 0;
	while (n1[j])
	{
		if (n1[j] != '.')
			nodot[i++] = n1[j];
		else
			dot = ft_strlen(n1) - i;
		j++;
	}
	if (dot >= 0 && dot < by)
		while (dot++ < by)
			nodot[i++] = '0';
	else if (dot == -1)
		while (by-- > 0)
			nodot[i++] = '0';
	return (nodot);
}

static char	*shiftresult(char *r, int by)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(by + ft_strlen(r) + 1);
	ft_memset(tmp, 0, ft_strlen(r) + by + 1);
	i = 0;
	j = 0;
	if (by >= (int)ft_strlen(r))
	{
		tmp[i++] = '0';
		tmp[i++] = '.';
		while (--by >= (int)ft_strlen(r))
			tmp[i++] = '0';
		while (j < (int)ft_strlen(r))
			tmp[i++] = r[j++];
	}
	else
		while (j < (int)ft_strlen(r))
			if (by > 0 && i == (int)ft_strlen(r) - by)
				tmp[i++] = '.';
			else
				tmp[i++] = r[j++];
	free(r);
	return (tmp);
}

static char	*ft_bignum_mtp(const char *n1, const char *n2)
{
	int		d[ft_strlen(n1) + ft_strlen(n2)];
	int		i;
	int		j;
	char	*str;

	ft_memset(d, !(i = -1), (ft_strlen(n1) + ft_strlen(n2)) * sizeof(int));
	while (++i < (int)ft_strlen(n1) && !(j = 0))
		while (j < (int)ft_strlen(n2))
		{
			d[i + j] += ((n1[i] - '0') * (n2[j] - '0'));
			j++;
		}
	str = ft_strnew(ft_strlen(n1) + ft_strlen(n2) + 1);
	i = 0;
	while (i < (int)(ft_strlen(n1) + ft_strlen(n2)))
	{
		if (i + 1 < (int)(ft_strlen(n1) + ft_strlen(n2)))
			d[i + 1] += d[i] / 10;
		str[i] = (d[i] % 10) + '0';
		i++;
	}
	while (i > 0 && str[--i] == '0')
		str[i] = '\0';
	return (ft_strrev(str));
}

char		*mtp(const char *n1, const char *n2)
{
	char	*d1;
	char	*d2;
	char	*r;
	int		shift;

	shift = ft_strlen(n1) - (ft_strichr(n1, '.') >= 0 ? ft_strichr(n1, '.') + 1
			: (signed int)ft_strlen(n1));
	shift = LARGEST(ft_strlen(n2) - (ft_strichr(n2, '.') >= 0 ?
			ft_strichr(n2, '.') + 1 : (signed int)ft_strlen(n2)),
			(unsigned long)shift);
	d1 = shiftdot(n1, shift);
	d2 = shiftdot(n2, shift);
	ft_strrev(d1);
	ft_strrev(d2);
	r = ft_bignum_mtp(d1, d2);
	free(d1);
	free(d2);
	r = shiftresult(r, shift * 2);
	return (r);
}
