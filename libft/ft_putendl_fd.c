/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 20:36:19 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 19:24:16 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putendl_fd(char const *s, int fd)
{
	int		nbprint;

	nbprint = 0;
	nbprint += ft_putstr_fd(s, fd);
	nbprint += ft_putchar_fd('\n', fd);
	return (nbprint);
}
