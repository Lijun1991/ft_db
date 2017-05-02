/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unumlen_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:53:49 by varnaud           #+#    #+#             */
/*   Updated: 2017/01/10 18:08:09 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_unumlen_base(unsigned long long n, int base)
{
	int		len;

	len = 1;
	while ((n /= base))
		len++;
	return (len);
}
