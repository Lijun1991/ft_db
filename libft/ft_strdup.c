/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 19:27:08 by varnaud           #+#    #+#             */
/*   Updated: 2017/04/11 17:44:55 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*tmp;

	dup = (char*)malloc(ft_strlen(s1) + 1);
	if (dup == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	tmp = dup;
	while ((*tmp++ = *s1++))
		;
	return (dup);
}
