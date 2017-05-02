/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 14:43:44 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:47:12 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*l;

	l = little;
	if (*l == '\0')
		return ((char*)big);
	while (len--)
	{
		if (*l == *big)
			l++;
		else
		{
			big -= (l - little);
			len += (l - little);
			l = little;
		}
		big++;
		if (*l == '\0')
			return ((char*)(big - (l - little)));
		if (*big == '\0')
			break ;
	}
	return (NULL);
}
