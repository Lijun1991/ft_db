/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 14:08:23 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:50:54 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnadd(char **dest, int n)
{
	char	*s;
	int		size;

	size = ft_strlen(*dest);
	s = ft_strnew(size + n);
	if (s == NULL)
		return (NULL);
	if (*dest != NULL)
	{
		ft_strcpy(s, *dest);
		free(*dest);
	}
	*dest = s;
	return (s);
}
