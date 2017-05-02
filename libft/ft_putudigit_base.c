/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putudigit_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 18:09:08 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:51:28 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putudigit_base(unsigned long long n, int base, int (*f)(int))
{
	int		nbprint;

	if (n >= (unsigned int)base)
	{
		nbprint = ft_putudigit_base(n / base, base, f) + 1;
		ft_putchar(f(n % base));
	}
	else
		nbprint = ft_putchar(f(n));
	return (nbprint);
}
