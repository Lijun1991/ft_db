/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 20:34:27 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 19:20:29 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putstr_fd(char const *s, int fd)
{
	size_t	i;
	int		nbprint;

	nbprint = 0;
	i = 0;
	while (s[i])
	{
		nbprint += ft_putchar_fd(s[i], fd);
		i++;
	}
	return (nbprint);
}
