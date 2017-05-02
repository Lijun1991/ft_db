/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 20:25:08 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:51:19 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnchar(char c, unsigned int n)
{
	int		nbprint;

	nbprint = 0;
	while (n--)
		nbprint += ft_putchar(c);
	return (nbprint);
}
