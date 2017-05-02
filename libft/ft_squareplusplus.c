/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_squareplusplus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 18:51:13 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:50:46 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_squareplusplus(char ***src, int c, int old, int len)
{
	char	**a;
	int		i;

	a = (char**)malloc(sizeof(char*) * (1 + len));
	a[len] = NULL;
	i = len;
	while (i--)
	{
		a[i] = ft_strnew(len);
		ft_memset(a[i], c, len);
		a[i][len] = '\0';
	}
	if (src == NULL)
		return (a);
	while (i++ < old - 1)
	{
		ft_memcpy(a[i], (*src)[i], old);
		free((*src)[i]);
	}
	free(*src);
	src = &a;
	return (a);
}
