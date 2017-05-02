/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:51:31 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:53:51 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnchar_fd(char c, unsigned int n, int fd)
{
	int		nbprint;

	nbprint = 0;
	while (n--)
		nbprint += ft_putchar_fd(c, fd);
	return (nbprint);
}
