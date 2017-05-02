/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putudigit_base_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:58:07 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:53:45 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putudigit_base_fd(unsigned long long n, int base, int (*f)(int),
		int fd)
{
	int		nbprint;

	if (n >= (unsigned int)base)
	{
		nbprint = ft_putudigit_base_fd(n / base, base, f, fd) + 1;
		ft_putchar_fd(f(n % base), fd);
	}
	else
		nbprint = ft_putchar_fd(f(n), fd);
	return (nbprint);
}
