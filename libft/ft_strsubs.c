/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:26:28 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/17 16:49:07 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubs(char *dest, const char *search, const char *by)
{
	char	*p;
	int		lenby;
	int		lens;

	p = ft_strstr(dest, search);
	if (p == NULL)
		return (dest);
	lenby = ft_strlen(by);
	lens = ft_strlen(search);
	ft_memcpy(p + lenby, p + lens, ft_strlen(p + lens) + 1);
	ft_memcpy(p, by, lenby);
	return (dest);
}
