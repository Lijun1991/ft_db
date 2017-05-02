/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 19:27:15 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:53:32 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *source, size_t size)
{
	unsigned char	*dup;
	size_t			i;

	dup = malloc(size);
	i = 0;
	while (i < size)
	{
		dup[i] = ((unsigned char*)source)[i];
		i++;
	}
	return (dup);
}
