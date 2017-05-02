/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 14:58:06 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:44:05 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char			*d;
	const char		*s;

	d = dest;
	s = src;
	while (n--)
	{
		*d++ = *s;
		if (*s == c)
			return ((void*)d);
		s++;
	}
	return (NULL);
}
