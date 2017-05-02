/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 19:27:41 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:48:17 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	char	*p;

	str = (char*)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	p = str;
	while (size)
	{
		*p++ = '\0';
		size--;
	}
	*p = '\0';
	return (str);
}
