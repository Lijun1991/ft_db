/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdigit_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:03:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:53:40 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putdigit_fd(long long nbr, int fd)
{
	int		nbprint;

	if (nbr < 0)
	{
		nbprint = 1;
		if (nbr <= -10)
			nbprint = ft_putdigit_fd(nbr / -10, fd) + 1;
		ft_putchar_fd(-(nbr % 10) + '0', fd);
	}
	else if (nbr >= 10)
	{
		nbprint = ft_putdigit_fd(nbr / 10, fd) + 1;
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else
		nbprint = ft_putchar_fd(nbr + '0', fd);
	return (nbprint);
}
