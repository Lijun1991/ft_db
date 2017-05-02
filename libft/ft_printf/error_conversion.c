/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 00:39:19 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/12 19:31:50 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int		error_conversion(t_flags *flags)
{
	char	err[2];

	err[0] = flags->conversion;
	err[1] = '\0';
	return (handle_string(flags, err));
}
