/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 00:01:03 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:53:05 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_hex(const unsigned char *data, size_t size, size_t i)
{
	size_t		a;
	const char	base[] = "0123456789abcdef";

	a = 0;
	while (a < 16 && a + i < size)
	{
		write(1, base + (data[a + i] >> 4), 1);
		write(1, base + (data[a + i] & 15), 1);
		write(1, " ", 1);
		a++;
	}
	while (a < 16)
	{
		write(1, "   ", 3);
		a++;
	}
}

static void	print_char(const unsigned char *data, size_t size, size_t i)
{
	size_t	a;

	a = 0;
	write(1, "| ", 2);
	while (a < 16 && a + i < size)
	{
		write(1, data[a + i] >= ' ' && data[a + i] <= '~' ?
				(char*)data + a + i : ".", 1);
		a++;
	}
}

void		ft_dump(const void *data, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		print_hex((const unsigned char *)data, size, i);
		print_char((const unsigned char *)data, size, i);
		write(1, "\n", 1);
		i += 16;
	}
}
