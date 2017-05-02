/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 20:38:46 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 19:31:58 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_fd(int n, int fd)
{
	int		nbprint;

	if (n < 0)
	{
		nbprint = 2;
		ft_putchar_fd('-', fd);
		if (n <= -10)
			nbprint = ft_putnbr_fd(n / -10, fd) + 1;
		ft_putchar_fd(-(n % 10) + '0', fd);
	}
	else if (n >= 10)
	{
		nbprint = ft_putnbr_fd(n / 10, fd) + 1;
		ft_putchar_fd((n % 10) + '0', fd);
	}
	else
		nbprint = ft_putchar_fd(n + '0', fd);
	return (nbprint);
}
