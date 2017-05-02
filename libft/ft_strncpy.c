/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 19:38:28 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:46:14 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	while (n--)
		if (*src == '\0')
			*tmp++ = 0;
		else
			*tmp++ = *src++;
	return (dest);
}
