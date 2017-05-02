/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 00:29:54 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:51:24 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putdigit(long long nbr)
{
	int		nbprint;

	if (nbr < 0)
	{
		nbprint = 1;
		if (nbr <= -10)
			nbprint = ft_putdigit(nbr / -10) + 1;
		ft_putchar(-(nbr % 10) + '0');
	}
	else if (nbr >= 10)
	{
		nbprint = ft_putdigit(nbr / 10) + 1;
		ft_putchar(nbr % 10 + '0');
	}
	else
		nbprint = ft_putchar(nbr + '0');
	return (nbprint);
}
