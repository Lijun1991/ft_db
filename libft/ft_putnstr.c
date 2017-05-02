/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 16:05:33 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:51:07 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnstr(const char *str, size_t n)
{
	ssize_t	i;

	i = 0;
	while (*str && n)
	{
		i += ft_putchar(*str);
		str++;
		n--;
	}
	return (i);
}
